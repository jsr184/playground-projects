#include "window-sdl2.h"
#include "../common/window.h"
#include "../../platform/sdl2/application-sdl2.h"
#include <SDL2/SDL_syswm.h>

namespace Framework
{

SDL_Window *WindowSDL2::getSDLWindow() const
{
  return window.get();
}

WindowSDL2::~WindowSDL2()
{
  auto wndId = SDL_GetWindowID(window.get());
  static_cast<ApplicationSDL2 &>(application).unregisterWindow(wndId);
}

void WindowSDL2::invalidate(Window &wnd)
{
  SDL_GL_MakeCurrent(window.get(), context);
  paintSignal.emit(wnd);
}

WindowSDL2::WindowSDL2(Application &app, const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h) :
  WindowImpl(app)
{
  window.reset(SDL_CreateWindow(name.c_str(), x, y, w, h, SDL_WINDOW_OPENGL));
  context = SDL_GL_CreateContext(window.get());
  static_cast<ApplicationSDL2 &>(app).registerWindow(SDL_GetWindowID(window.get()), *this);
}

void WindowSDL2::swapBuffers()
{
  SDL_GL_MakeCurrent(window.get(), context);
  SDL_GL_SetSwapInterval(0);
  SDL_GL_SwapWindow(window.get());
}

NativeWindow WindowSDL2::GetNativeWindow()
{
  NativeWindow retval;
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_GetWindowWMInfo(window.get(), &info);

#if defined(SDL_VIDEO_DRIVER_X11)
  if(info.subsystem == SDL_SYSWM_X11 )
  {
    retval.type = NativeWindowType::X11_XLIB;

    auto wnd = info.info.x11.window;
    auto display = info.info.x11.display;

    retval.x11.window = wnd;
    retval.x11.display = display;
    return retval;
  }
#endif
#if defined(SDL_VIDEO_DRIVER_WAYLAND)
  else if(info.subsystem == SDL_SYSWM_WAYLAND)
  {
    retval.type = NativeWindowType::WAYLAND;

    auto display = info.info.wl.display;
    auto surface = info.info.wl.surface;
    auto shellsurface = info.info.wl.shell_surface;

    retval.wl.display = display;
    retval.wl.shell_surface = shellsurface;
    retval.wl.surface = surface;
  }
#endif

  return retval;
}

}