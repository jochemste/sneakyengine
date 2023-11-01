#include "engine.hpp"

#include <iostream>

Engine::Engine() : m_engineState(EngineState::NOT_RUNNING) {}

Engine::~Engine() {
  if (this->m_engineState == EngineState::RUNNING) {
    stop();
  }
}

const int Engine::run() { return 0; }

int Engine::stop() {
  this->m_engineState = EngineState::STOPPED;
  return 0;
}
