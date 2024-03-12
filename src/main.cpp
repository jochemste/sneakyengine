#include "engine.hpp"

#include "logging.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  logging::Log().set_loglevel(logging::LogLevel::debug);
  logging::Log(logging::LogLevel::debug) << logging::LOG_START;
  logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Starting test application";

  Engine engine;
  int res = engine.run();
  if (res) {
    logging::Log(logging::LogLevel::critical)
        << logging::LOG_HEADER << "An error occurred. Error code: " << res;
  }
  engine.stop();
}
