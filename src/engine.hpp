#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "display.hpp"

enum class EngineState { RUNNING, PAUSED, STOPPED, NOT_RUNNING };

class Engine {

public:
  Engine();
  ~Engine();

  int run();
  int stop();

private:
  EngineState m_engine_state = EngineState::NOT_RUNNING;
  std::unique_ptr<IDisplay> m_display;
};

#endif
