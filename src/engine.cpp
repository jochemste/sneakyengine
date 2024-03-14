#include "engine.hpp"

#include "logging.hpp"
#include "process.hpp"

#include "display_proc_impl.hpp"
#include "event_proc.hpp"

Engine::Engine() : m_engine_state(EngineState::NOT_RUNNING) {
  Log(LogLevel::debug) << LOG_START;
  auto procman_fact = process::PROC_get_processmanager_factory();
  m_procman         = procman_fact->create_processmanager();
  Log(LogLevel::debug) << LOG_END;
}

Engine::~Engine() {
  Log(LogLevel::debug) << LOG_START;
  if (m_engine_state != EngineState::STOPPED) {
    stop();
  }
  Log(LogLevel::debug) << LOG_END;
}

int Engine::run() {
  Log(LogLevel::debug) << LOG_START;

  try {
    m_procman->start();

    // Add the main processes
    m_procman->provide(
        *EventHandlerProcessFactory()
             .createProcess(ProcessOwner::process_manager, "main_eventhandler")
             .release());
    m_procman->provide(
        *DisplayProcessFactory()
             .createProcess(ProcessOwner::process_manager, "main_display")
             .release());

    Log(LogLevel::info) << LOG_HEADER << "Engine is running";
  } catch (const ProcessException &exc) {
    Log(LogLevel::critical)
        << LOG_HEADER << "Fatal exception occurred: " << exc.what();
  } catch (...) {
    Log(LogLevel::critical)
        << LOG_HEADER << "Fatal unknown exception occurred ";
  }

  Log(LogLevel::debug) << LOG_END;
  return 0;
}

int Engine::stop() {
  Log(LogLevel::debug) << LOG_START;
  m_procman->stop();
  m_engine_state = EngineState::STOPPED;

  Log(LogLevel::info) << LOG_HEADER << "Engine stopped";
  Log(LogLevel::debug) << LOG_END;
  return 0;
}