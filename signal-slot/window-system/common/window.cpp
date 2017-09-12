#include "../../platform/common/application.h"
#include "window-impl.h"

namespace Framework
{

Window::Window(WindowImpl &impl)
  : window(impl)
{
}

Window::~Window()
{
  delete &window;
}

void Window::invalidate()
{
  window.invalidate(*this);
}

Window::PaintSignal &Window::paintSignal()
{
  return window.paintSignal;
};

Window::EventSignal &Window::eventSignal()
{
  return window.eventSignal;
};

auto &Window::getApplication()
{
  return window.application;
}

NativeWindow Window::GetNativeWindow()
{
  return window.GetNativeWindow();
}

}
