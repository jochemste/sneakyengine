#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

namespace event {

/// Eventhandler interface class
class IEventHandler {
public:
  /// @brief Start the event handler
  virtual void start() = 0;

  /// @brief Stop the event handler
  virtual void stop() = 0;
};

/// Factory class to create eventhandlers
class EventHandlerFactory {
public:
  /// @brief Create a default IEventHandler implementation
  std::unique_ptr<IEventHandler> create();
};

} // namespace event
#endif // EVENT_HPP
