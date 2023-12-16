#include "engine.hpp"

#include "display.hpp"
#include "logging.hpp"
#include "process.hpp"

Engine::Engine() : m_engine_state(EngineState::NOT_RUNNING) {}

Engine::~Engine() {
  if (this->m_engine_state == EngineState::RUNNING) {
    stop();
  }
}

int Engine::run() {
  if (PROC_init() != 0) {
    Log(LogLevel::critical) << LOG_HEADER << "Failed to initialise";
    return -1;
  }

  Log(LogLevel::info) << LOG_HEADER << "Engine is running";
  m_display = DIS_get_display_instance();
  m_display->start();

  int test_loops = 60;
  for (int i = 0; i < test_loops; i++) {
    m_display->refresh();
  }

  return 0;
}

int Engine::stop() {
  this->m_engine_state = EngineState::STOPPED;
  m_display->stop();
  PROC_quit();
  Log(LogLevel::info) << LOG_HEADER << "Engine stopped";
  return 0;
}
