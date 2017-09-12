#ifndef SIGNAL_SLOT_WINDOW_IMPL_H
#define SIGNAL_SLOT_WINDOW_IMPL_H

#include "../../system/common/signal.h"
#include "window.h"
namespace Framework
{

class Application;

class Window;

class AppEvent;

class WindowImpl
{
public:

  WindowImpl(Application &app);
  virtual ~WindowImpl();

  virtual void invalidate(Window &) = 0;
  virtual NativeWindow GetNativeWindow() = 0;

  Signal<void, Window &>             paintSignal{};
  Signal<bool, Window &, AppEvent &> eventSignal{};
  Application &application;
};

}

#endif //SIGNAL_SLOT_WINDOW_IMPL_H
