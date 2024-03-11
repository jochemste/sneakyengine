#include "inputpoller_sdl_impl.hpp"

#include "logging.hpp"

#include "SDL3/SDL.h"

namespace input {
  void InputPollerSDLImpl::poll(input::InputEvent &event) {
    Log(LogLevel::debug) << LOG_START;

    SDL_Event sdl_event;

    // Check for event, return if none
    if (SDL_PollEvent(&sdl_event) == 0) {
      event = input::InputEvent::no_event;
      Log(LogLevel::debug) << LOG_END << " - No event";
      return;
    }

    // Check event type
    switch (sdl_event.type) {
    case SDL_EVENT_QUIT:
      event = input::InputEvent::quit;
      break;
    default:
      Log(LogLevel::warning) << LOG_HEADER
                            << "Unknown event type: " << sdl_event.type;
      event = input::InputEvent::unknown;
      break;
    };

    Log(LogLevel::debug) << LOG_END;
  }
}
