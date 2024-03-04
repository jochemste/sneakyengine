#ifndef INPUTPOLLER_SDL_IMPL_HPP
#define INPUTPOLLER_SDL_IMPL_HPP

#include "input.hpp"

class InputPollerSDLImpl : public input::IInputPoller {
  virtual void poll(input::InputEvent &event) override;
};

#endif // INPUTPOLLER_SDL_IMPL_HPP
