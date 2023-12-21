#include "display_sdl_impl.hpp"

#include "logging.hpp"
#include "time.hpp"

// Temporary constexpr. Data will be retrieved differently in future iteration
constexpr const char *g_window_name = "SneakyEngine";
constexpr int g_window_width        = 680;
constexpr int g_window_height       = 480;
constexpr Uint32 g_window_flags     = SDL_WINDOW_OPENGL;
constexpr int g_window_fps          = 60;

DisplaySDLImpl::DisplaySDLImpl()
    : m_window(nullptr), m_surface(nullptr),
      m_tick_interval(utils::time::nsecond / g_window_fps) {}
DisplaySDLImpl::~DisplaySDLImpl() {}

void DisplaySDLImpl::start() {
  Log(LogLevel::info) << LOG_HEADER << "Starting display";

  m_window = SDL_CreateWindow(g_window_name, g_window_width, g_window_height,
                              g_window_flags);
  if (m_window == nullptr) {
    const std::string err_msg("Failed to create window");
    Log(LogLevel::critical) << LOG_HEADER << err_msg << ": " << SDL_GetError();
    throw DisplayException(err_msg);
  } else {
    m_surface = SDL_GetWindowSurface(m_window);
  }

  if (m_surface == nullptr) {
    const std::string err_msg("Failed to get surface from window");
    Log(LogLevel::critical) << LOG_HEADER << err_msg << ": " << SDL_GetError();
    throw DisplayException(err_msg);
  }

  m_next_frame_tick_nr = SDL_GetTicks() + m_tick_interval;
}
void DisplaySDLImpl::stop() {
  Log(LogLevel::info) << LOG_HEADER << "Stopping display";

  if (SDL_DestroyWindowSurface(m_window) != 0) {
    const std::string err_msg("Failed to destroy window surface");
    Log(LogLevel::error) << LOG_HEADER << err_msg;
    throw DisplayException(err_msg);
  }

  SDL_DestroyWindow(m_window);
}

void DisplaySDLImpl::refresh() {
  SDL_UpdateWindowSurface(m_window);
  this->wait_FPS();
}

// PRIVATE
void DisplaySDLImpl::wait_FPS() {
  auto current_tick = SDL_GetTicks();
  if (current_tick < m_next_frame_tick_nr) {
    SDL_Delay(m_next_frame_tick_nr - current_tick);
  }
  m_next_frame_tick_nr += m_tick_interval;
}
