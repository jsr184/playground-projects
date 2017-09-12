#ifndef SIGNAL_SLOT_GRAPHICS_DEVICE_H
#define SIGNAL_SLOT_GRAPHICS_DEVICE_H

#include <memory>

class GraphicsDeviceImpl;
class Window;
class Surface
namespace Framework
{
class GraphicsDevice
{
public:

  GraphicsDevice() = default;
  ~GraphicsDevice() = default;

  Surface CreateSurface( Window& window );

private:

  std::unique_ptr<GraphicsDeviceImpl> mImpl;

};
}

#endif //SIGNAL_SLOT_GRAPHICS_DEVICE_H
