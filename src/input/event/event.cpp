#include "event.hpp"
#include "eventhandler_impl.hpp"

namespace input {
  namespace event {
    std::unique_ptr<IEventHandler> EventHandlerFactory::create() {
      // Create eventhandler implementation
      return std::make_unique<EventHandlerImpl>();
    }
  } // namespace event
}