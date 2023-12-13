#include "display_sdl_impl.hpp"
#include "logging.hpp"

void DisplaySDLImpl::start() {
  Log(LogLevel::info) << LOG_HEADER << "Starting display";
}
void DisplaySDLImpl::stop() {
  Log(LogLevel::info) << LOG_HEADER << "Stopping display";
}
