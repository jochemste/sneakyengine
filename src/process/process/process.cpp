#include "process.hpp"
#include "processmanager_fact_impl.hpp"

#include "logging.hpp"

#include "SDL3/SDL.h"

int PROC_init() {
  Log(LogLevel::info) << LOG_HEADER << "Initialising Processes";
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    Log(LogLevel::critical) << LOG_HEADER << "Failed to initialise SDL";
    return -1;
  }

  return 0;
}

void PROC_quit() {
  Log(LogLevel::info) << LOG_HEADER << "Stopping Processes";
  SDL_Quit();
}

ProcessException::ProcessException(const char *message) : m_message(message) {}

ProcessException::ProcessException(const std::string &message)
    : ProcessException(message.c_str()) {}

const char *ProcessException::what() const noexcept { return m_message; }

namespace process {
std::unique_ptr<IProcessManagerFactory> PROC_get_processmanager_factory() {
  return std::make_unique<ProcessManagerFactoryImpl>();
}
} // namespace process
