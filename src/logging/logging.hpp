#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "ilog_instance.hpp"

#include <iostream>
#include <memory>
#include <sstream>

#define LOG_HEADER                \
  LOG_get_relative_path(__FILE__) \
      << ":" << __builtin_FUNCTION() << ":" << __LINE__ << " >> "
#define LOG_START LOG_HEADER << "Start function"
#define LOG_END   LOG_HEADER << "End function"

enum class LogLevel { critical, error, warning, info, debug };

/// @brief Return the relative path to a file, from the current path
const std::string LOG_get_relative_path(const std::string &filepath);

/// @brief Main logging
class Log {
public:
  Log(LogLevel log_level = LogLevel::error);
  Log(std::unique_ptr<ILogInstance> logger,
      LogLevel log_level = LogLevel::error);
  ~Log();

  /// @brief Flush the buffer
  void flush();

  void set_loglevel(LogLevel log_level);

  /// @brief Logging to be used as a stream
  template <typename T> Log &operator<<(T const &value) {
    m_buffer << value;
    return *this;
  }

protected:
private:
  /// Logging level to use for the logger implementation
  static LogLevel m_loglevel_app;

  /// Logging level of the current buffer
  LogLevel m_loglevel_buffer;

  /// The buffer to log
  std::ostringstream m_buffer;

  /// The implemented instance of the logger
  std::unique_ptr<ILogInstance> m_logger;
};

#endif // LOGGING_HPP
