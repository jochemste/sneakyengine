#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>

namespace input {

enum class InputEvent { quit };

class IInputPoller {
  virtual void poll(InputEvent &event) = 0;
};

class InputPollerFactory {
  std::unique_ptr<IInputPoller> create();
};

} // namespace input
#endif // INPUT_HPP
