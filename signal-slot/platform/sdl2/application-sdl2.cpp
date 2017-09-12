#include "application-sdl2.h"
#include "../../window-system/sdl2/window-factory-sdl2.h"
#include "../../window-system/sdl2/window-sdl2.h"
#include "../../window-system/common/window.h"
#include "../common/application.h"

#include <SDL2/SDL.h>

namespace Framework
{

ApplicationSDL2::ApplicationSDL2(const std::string &appName) :
  Application{appName}
{}

void ApplicationSDL2::onCreate(Application &)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  appRunning = true;
}

void ApplicationSDL2::onTerminate(Application &)
{
  appRunning = false;
}

void ApplicationSDL2::onIdle(Application &application)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      appRunning = false; // quit
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
      AppEvent appEvent;
      appEvent.eventType = AppEventType::eMouse;
      appEvent.mouse
              .posX      = event.motion
                                .x;
      appEvent.mouse
              .posY      = event.motion
                                .y;
      appEvent.mouse
              .pressed   = event.motion
                                .state;

      //eventSignal.emit( application, appEvent );
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      AppEvent appEvent;
      appEvent.eventType = AppEventType::eMouse;
      appEvent.mouse
              .posX      = event.button
                                .x;
      appEvent.mouse
              .posY      = event.button
                                .y;
      appEvent.mouse
              .pressed   = event.button
                                .clicks;

      eventSignal.emit(application, appEvent);
    }
    else if (event.type == SDL_WINDOWEVENT)
    {
      if (event.window
               .event == SDL_WINDOWEVENT_CLOSE)
      {
        AppEvent appEvent;
        appEvent.eventType = AppEventType::eWindow;
        appEvent.window
                .event     = WindowEvent::eClose;
        appEvent.window
                .uservalue = event.window
                                  .event;
        auto windowImpl = windowRegister[event.window
                                              .windowID];
        windowImpl->eventSignal
                  .emit(*windowImpl->getOwner(), appEvent);
      }
    }

  }
  tickSignal.emit(*this);
  for (auto &&wnd : windowRegister)
  {
    wnd.second
       ->swapBuffers();
  }
  SDL_Delay(16u);
}

void ApplicationSDL2::onFrameBegin(Application &application)
{
}

void ApplicationSDL2::onFrameEnd(Application &application)
{
}

bool ApplicationSDL2::isRunning(Application &application)
{
  return appRunning;
}

WindowFactory &ApplicationSDL2::getWindowFactory()
{
  if (windowFactory == nullptr)
  {
    windowFactory = new WindowFactorySDL2(*this);
  }
  return *windowFactory;
}

void ApplicationSDL2::registerWindow(uint32_t sdlWindow, WindowSDL2 &appWindow)
{
  windowRegister[sdlWindow] = &appWindow;
}

void ApplicationSDL2::unregisterWindow(uint32_t sdlWindow)
{
  auto it = windowRegister.find(sdlWindow);
  if (it != windowRegister.end())
  {
    windowRegister.erase(it);
  }
}

extern "C"
{
Application *CreateApplication(const char *appName)
{
  return new ApplicationSDL2(appName);
}
}

}