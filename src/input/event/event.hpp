#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

namespace event {

class IEventHandler {
public:
  /// @brief Start the event handler
  virtual void start() = 0;

  /// @brief Stop the event handler
  virtual void stop() = 0;
};

class EventHandlerFactory {
public:
  std::unique_ptr<IEventHandler> create();
};

} // namespace event
#endif // EVENT_HPP
