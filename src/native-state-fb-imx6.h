#ifndef GLMARK2_NATIVE_STATE_FB_IMX6_H_
#define GLMARK2_NATIVE_STATE_FB_IMX6_H_

#include "native-state.h"
#include <EGL/eglvivante.h>

class NativeStateFBIMX6 : public NativeState
{
public:
	NativeStateFBIMX6()
		: fbdpy_(0), fbwin_(0), properties_() {}
	~NativeStateFBIMX6();

	bool init_display();
    void* display() { return (void *)fbdpy_; }
    bool create_window(WindowProperties const& properties);
    void* window(WindowProperties& properties);
    void visible(bool v) { (void)v; }
    bool should_quit() { return false; }
    void flip() { }

private:
	EGLNativeDisplayType fbdpy_;
	EGLNativeWindowType fbwin_;
	WindowProperties properties_;
};

#endif /* GLMARK2_NATIVE_STATE_FB_IMX6_H_ */
