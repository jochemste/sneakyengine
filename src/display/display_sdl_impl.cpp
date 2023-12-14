#include "display_sdl_impl.hpp"
#include "logging.hpp"

void DisplaySDLImpl::start() {
  Log(LogLevel::info) << LOG_HEADER << "Starting display";
  m_window = SDL_CreateWindow("SneakyEngine", 680, 480, SDL_WINDOW_OPENGL);

  if (m_window == nullptr) {
    Log(LogLevel::critical) << "Failed to create window:" << SDL_GetError();
  }
}
void DisplaySDLImpl::stop() {
  Log(LogLevel::info) << LOG_HEADER << "Stopping display";

  // Temporary debug delay
  SDL_Delay(1000);

  SDL_DestroyWindow(m_window);
}
