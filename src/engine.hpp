#ifndef ENGINE_H
#define ENGINE_H

#include "process.hpp"

#include <memory>

enum class EngineState { RUNNING, PAUSED, STOPPED, NOT_RUNNING };

class Engine {

public:
  Engine();
  ~Engine();

  int run();
  int stop();

private:
  EngineState m_engine_state = EngineState::NOT_RUNNING;
  std::unique_ptr<process::IProcessManager> m_procman;
};

#endif
