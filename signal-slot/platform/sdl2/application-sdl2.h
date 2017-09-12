#ifndef SIGNAL_SLOT_APPLICATION_SDL2_H
#define SIGNAL_SLOT_APPLICATION_SDL2_H

#include "../common/application.h"
#include <map>

namespace Framework
{

class WindowFactory;
class WindowFactorySDL2;
class WindowSDL2;

class ApplicationSDL2 : public Application
{
public:

  ApplicationSDL2(const std::string &appName);

  void onCreate(Application &) override;
  void onTerminate(Application &) override;
  void onIdle(Application &application) override;
  void onFrameBegin(Application &application) override;
  void onFrameEnd(Application &application) override;
  bool isRunning(Application &application) override;

  WindowFactory &getWindowFactory() override;

  void registerWindow(uint32_t sdlWindow, WindowSDL2 &appWindow);
  void unregisterWindow(uint32_t sdlWindow);

private:

  bool appRunning{false};

  WindowFactorySDL2 *windowFactory{nullptr};

  std::map<uint32_t, WindowSDL2 *> windowRegister;
};

}
#endif //SIGNAL_SLOT_APPLICATION_SDL2_H
