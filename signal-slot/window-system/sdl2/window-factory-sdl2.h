#ifndef SIGNAL_SLOT_WINDOW_FACTORY_SDL2_H
#define SIGNAL_SLOT_WINDOW_FACTORY_SDL2_H

#include "../common/window-factory.h"

namespace Framework
{

class WindowFactorySDL2 final : public WindowFactory
{
public:

  WindowFactorySDL2(Application &app);
  virtual ~WindowFactorySDL2() = default;

  virtual std::unique_ptr<Window> createWindow(const std::string &name,
                                               int32_t x, int32_t y, uint32_t width, uint32_t height,
                                               void *userdata) override;

private:

  Application &application;
};

}
#endif //SIGNAL_SLOT_WINDOW_FACTORY_SDL2_H
