#ifndef SIGNAL_SLOT_WINDOW_FACTORY_X11_H
#define SIGNAL_SLOT_WINDOW_FACTORY_X11_H

#include "../common/window-factory.h"
#include <X11/Xlib.h>

namespace Framework
{

class WindowFactoryX11 final : public WindowFactory
{
public:

  WindowFactoryX11(Application &app, Display* display);
  virtual ~WindowFactoryX11() override;

  virtual std::unique_ptr<Window> createWindow(const std::string &name,
                                               int32_t x, int32_t y, uint32_t width, uint32_t height,
                                               void *userdata) override;

private:

  Display* mDisplay;
  Application &application;
};
}
#endif //SIGNAL_SLOT_WINDOW_FACTORY_X11_H
