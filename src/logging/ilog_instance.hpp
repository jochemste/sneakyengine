#ifndef ILOG_INSTANCE_HPP
#define ILOG_INSTANCE_HPP

#include <string>
namespace logging {
  class ILogInstance {
  public:
    virtual void log_critical(const std::string &message) = 0;
    virtual void log_error(const std::string &message)    = 0;
    virtual void log_warning(const std::string &message)  = 0;
    virtual void log_info(const std::string &message)     = 0;
    virtual void log_debug(const std::string &message)    = 0;
  };
}
#endif // ILOG_INSTANCE_HPP
