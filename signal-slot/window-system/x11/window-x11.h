#ifndef SIGNAL_SLOT_WINDOW_X11_H
#define SIGNAL_SLOT_WINDOW_X11_H

#include "../common/window-impl.h"
#include <memory>
#include <cstdint>
#include <X11/Xlib.h>

namespace Framework
{

class Window;

class WindowX11 : public WindowImpl
{
public:

  WindowX11(Application &app, ::Display* display, const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
  ~WindowX11() override;

  void invalidate(Window &window);

  NativeWindow GetNativeWindow() override;

private:

  ::Window mWindow { None };
  ::Display* mDisplay { nullptr };

};

}
#endif //SIGNAL_SLOT_WINDOW_X11_H
