#include <window-system/x11/window-factory-x11.h>
#include "application-x11.h"
#include <unistd.h>

namespace Framework
{
ApplicationX11::ApplicationX11(const std::string &appName)
: Application(appName)
{}

void ApplicationX11::onCreate(Application &)
{
  display = XOpenDisplay(nullptr);

  blackColor = BlackPixel(display, DefaultScreen(display));
  whiteColor = WhitePixel(display, DefaultScreen(display));

  appRunning = true;
}

void ApplicationX11::onTerminate(Application &)
{
  appRunning = false;
}

void ApplicationX11::onIdle(Application &application)
{
  // X11 application loop ( single iteration )
  XEvent event;
  while( XPending(display) )
  {
    XNextEvent(display, &event);
    if(XFilterEvent(&event, None))
    {
      continue;
    }

    if( event.type == Expose)
    {

    }
  }
  tickSignal.emit(*this);

  // handle window register
  usleep( 16000 );
}

void ApplicationX11::onFrameBegin(Application &application)
{

}

void ApplicationX11::onFrameEnd(Application &application)
{

}

bool ApplicationX11::isRunning(Application &application)
{
  return appRunning;
}

WindowFactory& ApplicationX11::getWindowFactory()
{
  if( !mWindowFactory )
  {
    display = XOpenDisplay( nullptr );
    mWindowFactory = new WindowFactoryX11( *this, display );
  }
  return *mWindowFactory;
}

extern "C"
{
Application *CreateApplication(const char *appName)
{
  return new ApplicationX11(appName);
}
}

}