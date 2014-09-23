#include "native-state-fb-imx6.h"
#include "log.h"

NativeStateFBIMX6::~NativeStateFBIMX6()
{
	if (fbdpy_) {
		if (fbwin_)
			fbDestroyWindow(fbwin_);
		fbDestroyDisplay(fbdpy_);
	}
}

bool NativeStateFBIMX6::init_display()
{
	if (!fbdpy_) {
		fbdpy_ = fbGetDisplayByIndex(0);
		if (!fbdpy_) {
			Log::error("Error: FB display create fail!\n");
			return false;
		}
	}

	return true;
}

void* NativeStateFBIMX6::window(WindowProperties& properties)
{
	properties = properties_;
	return (void *)fbwin_;
}

bool NativeStateFBIMX6::create_window(WindowProperties const& properties)
{
	if (!fbdpy_) {
		Log::error("Error: FB display has not been initialized!\n");
		return false;
	}

	/* Recreate an existing window only if it has actually been resized */
	if (fbwin_) {
		if (properties_.fullscreen != properties.fullscreen ||
            (properties.fullscreen == false &&
             (properties_.width != properties.width ||
              properties_.height != properties.height)))
		{
            fbDestroyWindow(fbwin_);
            fbwin_ = 0;
        }
        else
        {
            return true;
        }
	}

	/* Set desired attributes */
    properties_.fullscreen = properties.fullscreen;
    properties_.visual_id = properties.visual_id;

    if (properties_.fullscreen) {
        /* Get the screen size */
		fbGetDisplayGeometry(fbdpy_, &properties_.width, &properties_.height);
    }
    else {
        properties_.width = properties.width;
        properties_.height = properties.height;
    }

	fbwin_ = fbCreateWindow(fbdpy_, 0, 0, properties_.width, properties_.height);
	if (!fbwin_) {
		Log::error("Error: FB create window fail!\n");
		return false;
	}

	return true;
}



