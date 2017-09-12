#include "window-x11.h"
#include "../../platform/x11/application-x11.h"
#include <X11/Xutil.h>

namespace Framework
{

WindowX11::WindowX11(Application &app, ::Display* display,
                     const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
: WindowImpl(app)
{
  mDisplay = display;
  mWindow = XCreateSimpleWindow( display, RootWindow( display, DefaultScreen(display)), x, y, w, h, 1, 0, BlackPixel(display, DefaultScreen(display)));
  
  XSizeHints    hints = {0};
  hints.flags  = PPosition | PSize;
  hints.x      = x;
  hints.y      = y;
  hints.width  = w;
  hints.height = h;
  XSetNormalHints( display, mWindow, &hints );
  XMapWindow( display, mWindow );
  XFlush( display );
}

WindowX11::~WindowX11()
{
  XDestroyWindow( mDisplay, mWindow );
}

void WindowX11::invalidate(Window &window)
{

}

NativeWindow WindowX11::GetNativeWindow()
{

}

}