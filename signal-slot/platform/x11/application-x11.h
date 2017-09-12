#ifndef SIGNAL_SLOT_APPLICATION_X11_H
#define SIGNAL_SLOT_APPLICATION_X11_H

#include "../common/application.h"
#include <X11/Xlib.h>

namespace Framework
{

class WindowFactoryX11;
class ApplicationX11 : public Application
{
public:

  ApplicationX11(const std::string &appName);

  void onCreate(Application &) override;
  void onTerminate(Application &) override;
  void onIdle(Application &application) override;
  void onFrameBegin(Application &application) override;
  void onFrameEnd(Application &application) override;
  bool isRunning(Application &application) override;

  WindowFactory &getWindowFactory() override;

private:

  WindowFactoryX11* mWindowFactory { nullptr };

  bool appRunning{false};
  ::Display* display{nullptr};

  int blackColor, whiteColor;

};

}


#endif //SIGNAL_SLOT_APPLICATION_X11_H
