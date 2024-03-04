#include "inputpoller_sdl_impl.hpp"

#include "logging.hpp"

#include "SDL3/SDL.h"

void InputPollerSDLImpl::poll(input::InputEvent &event) {
  Log(LogLevel::debug) << LOG_START;

  SDL_Event sdl_event;
  SDL_PollEvent(&sdl_event);
  switch (sdl_event.type) {
  case SDL_EVENT_QUIT:
    event = input::InputEvent::quit;
    break;
  default:
    Log(LogLevel::warning) << LOG_HEADER
                           << "Unknown event type: " << sdl_event.type;
  };

  Log(LogLevel::debug) << LOG_END;
}
