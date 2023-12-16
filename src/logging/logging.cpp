#include "logging.hpp"
#include "log_sdl_impl.hpp"

LogLevel Log::m_loglevel_app = LogLevel::error;

Log::Log(LogLevel log_level) : Log(std::make_unique<LogSDLImpl>(), log_level) {}

Log::Log(std::unique_ptr<ILogInstance> logger, LogLevel log_level)
    : m_loglevel_buffer(log_level), m_logger(std::move(logger)) {}

Log::~Log() { flush(); }

void Log::flush() {
  if (m_buffer.tellp() == 0) {
    return;
  }

  m_buffer << std::endl;
  if (m_loglevel_buffer <= m_loglevel_app) {
    switch (m_loglevel_buffer) {
    case LogLevel::critical:
      m_logger->log_critical(m_buffer.str());
      break;
    case LogLevel::error:
      m_logger->log_error(m_buffer.str());
      break;
    case LogLevel::info:
      m_logger->log_info(m_buffer.str());
      break;
    case LogLevel::warning:
      m_logger->log_info(m_buffer.str());
      break;
    case LogLevel::debug:
      m_logger->log_debug(m_buffer.str());
      break;
    default:
      break;
    };
  }
  m_buffer.str(std::string());
};

void Log::set_loglevel(LogLevel log_level) { m_loglevel_app = log_level; }
