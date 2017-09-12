#ifndef SIGNAL_SLOT_APPLICATION_H_H
#define SIGNAL_SLOT_APPLICATION_H_H

#include "../../system/common/signal.h"
#include <memory>

namespace Framework
{

enum class AppEventType : uint32_t
{
  eApplication,
  eWindow,
  eTouch,
  eMouse,
  eUndefined
};

enum class WindowEvent
{
  eCreate,
  eDestroy,
  eMinimize,
  eMaximize,
  eClose,
};

struct AppEvent
{
  AppEventType eventType;
  union
  {
    struct
    {
      uint32_t posX;
      uint32_t posY;
      uint32_t pressed;
    } mouse;
    struct
    {
      WindowEvent event;
      void *windowPtr;
      uint32_t uservalue;
    } window;
  };
};

class WindowFactory;

class Window;

class AppEvent;

class Application
{
public:

  static std::unique_ptr<Application> New(const std::string &appName);

  Application();
  Application(const std::string &_appName);

  virtual ~Application();

  virtual void onCreate(Application &)
  {};

  virtual void onTerminate(Application &)
  {};

  virtual void onIdle(Application &)
  {};

  virtual void onFrameBegin(Application &)
  {}

  virtual void onFrameEnd(Application &)
  {}

  virtual bool isRunning(Application &)
  { return false; };

  virtual WindowFactory &getWindowFactory() = 0;

  std::unique_ptr<class Window> CreateWindow(const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

  void runMain(int argc, char **argv)
  {
    create();

    while (isRunning(*this))
    {
      frameBegin();

      idle();

      frameEnd();
    }
    terminate();
  }

private:

  void create();

  void terminate();

  void frameBegin();

  void frameEnd();

  void idle();

public:

  std::string appName{};

  Signal<void, Application &>             willCreateSignal{};
  Signal<void, Application &>             didCreateSignal{};
  Signal<void, Application &>             willTerminateSignal{};
  Signal<void, Application &>             didTerminateSignal{};
  Signal<void, Application &>             tickSignal{};
  Signal<bool, Application &, AppEvent &> eventSignal{};
  Signal<void, Application &>             beginFrameSignal{};
  Signal<void, Application &>             endFrameSignal{};

};

}
#endif //SIGNAL_SLOT_APPLICATION_H_H
