#include "window-factory-sdl2.h"
#include "window-sdl2.h"
#include "../common/window.h"

namespace Framework
{

WindowFactorySDL2::WindowFactorySDL2(Application &app) : WindowFactory(app),
                                                         application(app)
{

}

std::unique_ptr<Window> WindowFactorySDL2::createWindow(const std::string &name,
                                                        int32_t x, int32_t y, uint32_t width, uint32_t height,
                                                        void *userdata)
{
  auto retval = std::make_unique<Window>(
    *(new WindowSDL2(application, name, x, y, width, height))
  );
  retval->getImpl<WindowSDL2>()
        .setOwner(retval.get());
  return retval;
}

}