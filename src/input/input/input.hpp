#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>

namespace input {

/// Events returned by IInputPoller
enum class InputEvent { no_event, quit };

/// Input polling class, to read user input
class IInputPoller {
public:
  virtual void poll(InputEvent &event) = 0;
};

/// Factory class to create inputpollers
class InputPollerFactory {
public:
  std::unique_ptr<IInputPoller> create();
};

} // namespace input
#endif // INPUT_HPP
