#include "window-factory-x11.h"
#include "window-x11.h"

namespace Framework
{

WindowFactoryX11::WindowFactoryX11(Application &app, ::Display* display) : WindowFactory(app),
                                                         application(app), mDisplay(display)
{

}

WindowFactoryX11::~WindowFactoryX11()
{

}

std::unique_ptr<Window> WindowFactoryX11::createWindow(const std::string &name,
                                                        int32_t x, int32_t y, uint32_t width, uint32_t height,
                                                        void *userdata)
{

  auto retval = std::make_unique<Window>(
    *(new WindowX11(application, mDisplay, name, x, y, width, height))
  );
  return retval;
}

}