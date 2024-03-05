#ifndef INPUTPOLLER_SDL_IMPL_HPP
#define INPUTPOLLER_SDL_IMPL_HPP

#include "input.hpp"

/// SDL implementation of IInputPoller
class InputPollerSDLImpl : public input::IInputPoller {
public:
  /// SDL implementation of event handling
  virtual void poll(input::InputEvent &event) override;
};

#endif // INPUTPOLLER_SDL_IMPL_HPP
