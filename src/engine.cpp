#include "engine.hpp"

#include "display_proc_impl.hpp"
#include "event.hpp"
#include "logging.hpp"
#include "process.hpp"

Engine::Engine() : m_engine_state(EngineState::NOT_RUNNING) {
  logging::Log(logging::LogLevel::debug) << logging::LOG_START;
  auto procman_fact = process::PROC_get_processmanager_factory();
  m_procman         = procman_fact->create_processmanager();
  logging::Log(logging::LogLevel::debug) << logging::LOG_END;
}

Engine::~Engine() {
  logging::Log(logging::LogLevel::debug) << logging::LOG_START;
  if (m_engine_state != EngineState::STOPPED) {
    stop();
  }
  logging::Log(logging::LogLevel::debug) << logging::LOG_END;
}

int Engine::run() {
  logging::Log(logging::LogLevel::debug) << logging::LOG_START;

  auto eventhandler = input::event::EventHandlerFactory().create();

  try {
    m_procman->start();

    m_procman->provide(
        *display::displayProcess::DisplayProcessFactory()
             .createProcess(process::ProcessOwner::process_manager, "main_display")
             .release());

    logging::Log(logging::LogLevel::info) << logging::LOG_HEADER << "Engine is running";
    eventhandler->start();
  } catch (const process::ProcessException &exc) {
    logging::Log(logging::LogLevel::critical)
        << logging::LOG_HEADER << "Fatal exception occurred: " << exc.what();
  } catch (...) {
    logging::Log(logging::LogLevel::critical)
        << logging::LOG_HEADER << "Fatal unknown exception occurred ";
  }

  logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  return 0;
}

int Engine::stop() {
  logging::Log(logging::LogLevel::debug) << logging::LOG_START;
  m_procman->stop();
  m_engine_state = EngineState::STOPPED;

  logging::Log(logging::LogLevel::info) << logging::LOG_HEADER << "Engine stopped";
  logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  return 0;
}
