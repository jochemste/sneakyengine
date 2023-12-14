#include "engine.hpp"

#include "logging.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  Log().set_loglevel(LogLevel::debug);
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Starting test application";

  Engine engine;
  int res = engine.run();
  if (res) {
    Log(LogLevel::critical)
        << LOG_HEADER << "An error occurred. Error code: " << res;
  }
  engine.stop();
}
