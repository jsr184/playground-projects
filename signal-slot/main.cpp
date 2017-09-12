#include <iostream>
#include <vector>
#include <functional>

#include <GL/gl.h>
#include <memory>

#include "platform/common/application.h"
#include "window-system/common/window.h"

using namespace Framework;

class Example : public IConnectable
{
public:
  Example( std::unique_ptr<Application> app ) : application( std::move(app) )
  {
    application->didCreateSignal().connect( *this, &Example::onCreate );
    application->willTerminateSignal().connect( *this, &Example::onTerminate );
    application->tickSignal.connect( *this, &Example::tick );
    application->eventSignal.connect( *this, &Example::event );

    application->runMain( 0, nullptr );
  }

  void onCreate( Application& app )
  {
    window0 = app.CreateWindow("Window0", 0, 0, 320, 200);
    window1 = app.CreateWindow("Window1", 700, 700, 320, 200 );
    window2 = app.CreateWindow("Window2", 200, 200, 200, 200 );

    window0->paintSignal().connect( *this, &Example::paint0 );
    window1->paintSignal().connect( *this, &Example::paint1 );
    window2->paintSignal().connect( *this, &Example::paint1 );
    window0->eventSignal().connect( *this, &Example::windowEventHandler);
    window1->eventSignal().connect( *this, &Example::windowEventHandler);
  }

  bool windowEventHandler( Window& window, AppEvent& appEvent )
  {
    if( appEvent.window.event == WindowEvent::eClose )
    {
      std::cout << "Window event: " << appEvent.window.uservalue << std::endl;
      if( &window == window0.get() )
        window0.reset();
      if( &window == window1.get() )
        window1.reset();
    }

    return true;
  }

  void onTerminate( Application& app )
  {
    std::cout << "terminated\n";
  }

  void paint0( Window& window )
  {
    //std::cout << "paint0\n";
    static float col = 1.0f;
    col -= 0.02f;
    if( col < 0.0f)
      col += 1.0f;
    //std::cout << "Tick!\n";
    glDisable(GL_SCISSOR_TEST );
    glScissor( 0, 0, 640, 480 );
    glClearColor( col, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
  }

  void paint1( Window& window )
  {
    //std::cout << "paint1\n";
    static float col = 1.0f;
    col -= 0.02f;
    if( col < 0.0f)
      col += 1.0f;
    //std::cout << "Tick!\n";
    glDisable(GL_SCISSOR_TEST );
    glScissor( 0, 0, 640, 480 );
    glClearColor( 0.0f, 0.0f, col, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
  }

  void tick( Application& app )
  {
    if(window0)
      window0->invalidate();
    if(window1)
      window1->invalidate();
    if(window2)
      window2->invalidate();
  }

  bool event( Application& app, AppEvent& e )
  {
    return true;
  }

  std::unique_ptr<Application> application;

  std::unique_ptr<Window> window0;
  std::unique_ptr<Window> window1;
  std::unique_ptr<Window> window2;
};

int main()
{
  // create SDL app
  Example example(Application::New("TestApp"));

  return 0;
}