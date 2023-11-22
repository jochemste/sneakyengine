#ifndef ENGINE_H
#define ENGINE_H

enum class EngineState { RUNNING, PAUSED, STOPPED, NOT_RUNNING };

class Engine {

public:
  Engine();
  ~Engine();

  int run();
  int stop();

private:
  EngineState m_engineState = EngineState::NOT_RUNNING;
};

#endif
