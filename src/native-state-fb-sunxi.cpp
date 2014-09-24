#include "native-state-fb-sunxi.h"
#include "log.h"

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>

NativeStateFBSUNXI::NativeStateFBSUNXI()
    : properties_()
{
	fbwin_.width = 0;
	fbwin_.height = 0;
}

void* NativeStateFBSUNXI::window(WindowProperties& properties)
{
	properties = properties_;
	return &fbwin_;
}

bool NativeStateFBSUNXI::create_window(WindowProperties const& properties)
{
	/* Don't support window resize */
	if (fbwin_.width)
		return true;

	/* Set desired attributes */
	properties_.fullscreen = properties.fullscreen;
	properties_.visual_id = properties.visual_id;

	if (properties_.fullscreen) {
		/* Get the screen size */
		int fd = open("/dev/fb0", O_RDONLY);
		if (fd < 0) {
			Log::error("Error: Failed to open fb to detect screen resolution!\n");
			return false;
		}

		struct fb_var_screeninfo vinfo;
		if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) < 0) {
			Log::error("Error: Could not get variable screen info\n");
			close(fd);
			return false;
		}

		close(fd);

		properties_.width = vinfo.xres;
		properties_.height = vinfo.yres;
	}
	else {
		properties_.width = properties.width;
		properties_.height = properties.height;
    }

	fbwin_.width = properties_.width;
	fbwin_.height = properties_.height;

	return true;
}


