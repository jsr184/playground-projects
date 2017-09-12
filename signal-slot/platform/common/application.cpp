#include "application.h"
#include "../../window-system/common/window-factory.h"
#include "../../window-system/common/window.h"
#include "../../window-system/common/window-impl.h"

extern "C" Framework::Application* CreateApplication(const char*);

namespace Framework
{

Application::Application() = default;

Application::Application(const std::string &_appName) : appName{_appName}
{

}

Application::~Application() = default;

void Application::create()
{
  willCreateSignal.emit(*this);

  onCreate(*this);

  didCreateSignal.emit(*this);
};

void Application::terminate()
{
  willTerminateSignal.emit(*this);

  onTerminate(*this);

  didTerminateSignal.emit(*this);
};

void Application::frameBegin()
{
  beginFrameSignal.emit(*this);
  onFrameBegin(*this);
}

void Application::frameEnd()
{
  onFrameEnd(*this);
  endFrameSignal.emit(*this);
}

void Application::idle()
{
  onIdle(*this);
}

std::unique_ptr<Window>
Application::CreateWindow(const std::string &name, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  return std::move(getWindowFactory().createWindow(name, x, y, w, h, nullptr));
}

std::unique_ptr<Application> Application::New(const std::string &appName)
{
  auto retval = std::unique_ptr<Application>();
  retval.reset(CreateApplication(appName.c_str()));
  return retval;
}

}