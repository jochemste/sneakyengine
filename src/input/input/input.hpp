#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>

namespace input {

enum class InputEvent { quit };

class IInputPoller {
public:
  virtual void poll(InputEvent &event) = 0;
};

class InputPollerFactory {
public:
  std::unique_ptr<IInputPoller> create();
};

} // namespace input
#endif // INPUT_HPP
