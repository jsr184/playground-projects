#ifndef SIGNAL_SLOT_WINDOW_FACTORY_H
#define SIGNAL_SLOT_WINDOW_FACTORY_H

#include <memory>

namespace Framework
{

class Window;

class Application;

class WindowFactory
{
public:

  WindowFactory(Application &app)
  {}

  virtual ~WindowFactory() {}

  virtual std::unique_ptr<Window> createWindow(const std::string &name,
                                               int32_t x, int32_t y, uint32_t width, uint32_t height,
                                               void *userdata) = 0;
};

}
#endif //SIGNAL_SLOT_WINDOW_FACTORY_H
