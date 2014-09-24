#ifndef GLMARK2_NATIVE_STATE_FB_SUNXI_H_
#define GLMARK2_NATIVE_STATE_FB_SUNXI_H_

#include "native-state.h"
#include <EGL/egl.h>

class NativeStateFBSUNXI : public NativeState
{
public:
	NativeStateFBSUNXI();

	bool init_display() { return true; }
    void* display() { return (void *)EGL_DEFAULT_DISPLAY; }
    bool create_window(WindowProperties const& properties);
    void* window(WindowProperties& properties);
    void visible(bool v) { (void)v; }
    bool should_quit() { return false; }
    void flip() { }

private:
	mali_native_window fbwin_;
	WindowProperties properties_;
};

#endif /* GLMARK2_NATIVE_STATE_FB_SUNXI_H_ */
