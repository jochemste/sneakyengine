#include "ilog_instance.hpp"

#include <SDL3/SDL_log.h>

namespace logging {
class LogSDLImpl : public ILogInstance {
  public:
    LogSDLImpl() {
      if (!m_is_initialised) {
        SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, SDL_LOG_PRIORITY_VERBOSE);
        m_is_initialised = true;
        log_info("Logging initialised");
      }
    };
    virtual void log_critical(const std::string &message) {
      SDL_LogCritical(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
    }
    virtual void log_error(const std::string &message) {
      SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
    }
    virtual void log_warning(const std::string &message) {
      SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
    }
    virtual void log_info(const std::string &message) {
      SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
    }
    virtual void log_debug(const std::string &message) {
      SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "%s", message.c_str());
    }

  private:
    void _log(const std::string &message) { SDL_Log("%s", message.c_str()); }

    static bool m_is_initialised;
  };
}

bool LogSDLImpl::m_is_initialised = false;
