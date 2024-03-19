#include "display_sdl_impl.hpp"

#include "logging.hpp"
#include "time.hpp"

#include <string>

namespace display {
  // Temporary constexpr. Data will be retrieved differently in future iteration
  constexpr const char *g_window_name = "SneakyEngine";
  constexpr int g_window_width        = 680;
  constexpr int g_window_height       = 480;
  constexpr Uint32 g_window_flags     = SDL_WINDOW_OPENGL;
  constexpr int g_window_fps          = 60;

  static const std::string display_state_to_str(DisplayState state);

  DisplaySDLImpl::DisplaySDLImpl()
      : m_window(nullptr), m_surface(nullptr), m_state(DisplayState::not_running),
        m_tick_interval(utils::time::nsecond / g_window_fps) {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }
  DisplaySDLImpl::~DisplaySDLImpl() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void DisplaySDLImpl::start() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START << " - Starting display";

    m_window = SDL_CreateWindow(g_window_name, g_window_width, g_window_height,
                                g_window_flags);
    m_state  = DisplayState::running;

    // Failed to create window error
    if (m_window == nullptr) {
      m_state = DisplayState::failed;
      const std::string err_msg("Failed to create a window");
      logging::Log(logging::LogLevel::critical) << logging::LOG_HEADER << err_msg
                              << "(SDL): " << SDL_GetError() << " - " << logging::LOG_END;
      SDL_ClearError();
      throw DisplayException(err_msg);
    } else {
      m_surface = SDL_GetWindowSurface(m_window);
    }

    if (m_surface == nullptr) {
      m_state = DisplayState::failed;
      const std::string err_msg("Failed to get surface from window");
      logging::Log(logging::LogLevel::critical) << logging::LOG_HEADER << err_msg
                              << "(SDL): " << SDL_GetError() << " - " << logging::LOG_END;
      SDL_ClearError();
      throw DisplayException(err_msg);
    }

    m_next_frame_tick_nr = SDL_GetTicks() + m_tick_interval;

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void DisplaySDLImpl::stop() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START << " - Stopping display";

    // Try to destroy window surface and throw an error if failed, while m_state
    // is running
    if ((SDL_DestroyWindowSurface(m_window) != 0) &&
        (m_state == DisplayState::running)) {
      const std::string err_msg("Failed to destroy window surface, state=" +
                                display_state_to_str(m_state));
      logging::Log(logging::LogLevel::error) << logging::LOG_HEADER << err_msg << " - " << logging::LOG_END;
      throw DisplayException(err_msg);
    }
    m_state = DisplayState::stopping;

    // Destroy window
    SDL_DestroyWindow(m_window);
    m_state = DisplayState::finished;

    logging::Log(logging::LogLevel::debug) << logging::LOG_END << " - Stopped display";
  }

  void DisplaySDLImpl::refresh() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    SDL_UpdateWindowSurface(m_window);
    this->wait_FPS();
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  // PRIVATE
  void DisplaySDLImpl::wait_FPS() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;

    Uint64 current_tick = SDL_GetTicks();
    if (current_tick < m_next_frame_tick_nr) {
      SDL_Delay(static_cast<Uint32>(m_next_frame_tick_nr - current_tick));
    }
    m_next_frame_tick_nr += m_tick_interval;

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  static const std::string display_state_to_str(DisplayState state) {
    std::string state_str = "";
    switch (state) {
    case DisplayState::running:
      return "DisplayState::running";
    case DisplayState::not_running:
      return "DisplayState::not_running";
    case DisplayState::stopping:
      return "DisplayState::stopping";
    case DisplayState::finished:
      return "DisplayState::finished";
    case DisplayState::failed:
      return "DisplayState::failed";
    default:
      return "Unknown DisplayState";
    }
  }
}