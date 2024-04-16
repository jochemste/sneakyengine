#include "input.hpp"

#include "inputpoller_sdl_impl.hpp"

namespace input {
  std::unique_ptr<IInputPoller> InputPollerFactory::create() {
    return std::make_unique<InputPollerSDLImpl>();
  }
} // namespace input
