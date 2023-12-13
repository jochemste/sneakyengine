#include "engine.hpp"
#include "display.hpp"
#include "logging.hpp"

Engine::Engine() : m_engine_state(EngineState::NOT_RUNNING) {}

Engine::~Engine() {
  if (this->m_engine_state == EngineState::RUNNING) {
    stop();
  }
}

int Engine::run() {
  Log(LogLevel::info) << LOG_HEADER << "Engine is running";
  std::unique_ptr<IDisplay> display = DIS_get_display_instance();
  display->start();
  return 0;
}

int Engine::stop() {
  this->m_engine_state = EngineState::STOPPED;
  Log(LogLevel::info) << LOG_HEADER << "Engine stopped";
  return 0;
}
