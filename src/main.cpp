#include "engine.hpp"

#include <logging.hpp>

#include <iostream>

int main(int /*argc*/, char ** /*argv*/) {
  Log().set_loglevel(LogLevel::debug);
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Starting test application";

  Engine engine;
  int res = engine.run();
  if (res) {
    std::cout << "An error occurred. Error code: " << res << std::endl;
  }
  engine.stop();
}
