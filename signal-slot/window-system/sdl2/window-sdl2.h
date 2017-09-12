#ifndef SIGNAL_SLOT_WINDOW_SDL2_H
#define SIGNAL_SLOT_WINDOW_SDL2_H

#include "../common/window-impl.h"
#include <SDL2/SDL.h>
#include <memory>
#include <cstdint>

namespace Framework
{

class Window;

class WindowSDL2 : public WindowImpl
{
  // deleter
  struct SDLWindowDefaultDelete
  {
    void operator()(SDL_Window *ptr)
    {
      SDL_DestroyWindow(ptr);
    }
  };

  using UWindow = std::unique_ptr<SDL_Window, SDLWindowDefaultDelete>;

public:

  void invalidate(Window &window);

  WindowSDL2(Application &app, const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
  ~WindowSDL2() override;
  SDL_Window *getSDLWindow() const;

  void setOwner(Window *ownerWindow)
  {
    owner = ownerWindow;
  }

  Window *getOwner()
  {
    return owner;
  }

  void swapBuffers();

  NativeWindow GetNativeWindow() override;

private:

  Window *owner{nullptr};
  UWindow       window;
  SDL_GLContext context;

};

}
#endif //SIGNAL_SLOT_WINDOW_SDL2_H
