#ifndef SIGNAL_SLOT_WINDOW_H_H
#define SIGNAL_SLOT_WINDOW_H_H

#include <memory>

namespace Framework
{
enum class NativeWindowType
{
  UNSUPPORTED,
  X11_XLIB,
  X11_XCB,
  WIN32,
  WAYLAND
};

struct NativeWindow
{
  NativeWindowType type { NativeWindowType::UNSUPPORTED };
  union
  {
    struct
    {
      unsigned long window;
      void*         display;
    } x11;
    struct
    {
      void* display;
      void* shell_surface;
      void* surface;
    } wl;
  };
};

class Application;

class AppEvent;

class WindowImpl;

class Window
{
public:

  using PaintSignal = Signal<void, Window &>;
  using EventSignal = Signal<bool, Window &, AppEvent &>;

  Window(WindowImpl &impl);
  ~Window();

  void invalidate();
  PaintSignal &paintSignal();
  EventSignal &eventSignal();
  auto &getApplication();

  template<typename T>
  T &getImpl()
  {
    return *(static_cast<T *>(&window));
  }

  NativeWindow GetNativeWindow();

private:

  WindowImpl &window;
};

}
#endif //SIGNAL_SLOT_WINDOW_H_H
