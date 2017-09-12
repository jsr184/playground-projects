#include "window-impl.h"
#include "../../platform/common/application.h"

namespace Framework
{

WindowImpl::WindowImpl(Application &app) : application(app)
{
}

WindowImpl::~WindowImpl() = default;

}

