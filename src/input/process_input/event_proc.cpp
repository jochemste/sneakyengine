#include "event_proc.hpp"

#include "event.hpp"
#include "logging.hpp"
#include "process.hpp"

#include <memory>
#include <mutex>

namespace input {
  namespace process_input {
    class EventHandlerProcessImpl : public process::IProcess {
    public:
      EventHandlerProcessImpl() = delete;
      EventHandlerProcessImpl(const process::ProcessOwner &owner, const std::string &name);
      ~EventHandlerProcessImpl();

      virtual void execute(int id) override;
      virtual void kill() override;
      virtual process::ProcessState get_state() override;
      virtual process::ProcessOwner get_owner() override;
      virtual void get_name(std::string &name) override;

    private:
      void update_state(const process::ProcessState &state);

      process::ProcessOwner m_owner;
      int m_process_id;
      std::string m_name;
      process::ProcessState m_state;
      std::unique_ptr<event::IEventHandler> m_eventhandler;
      std::mutex m_state_mutex;
    };

    std::unique_ptr<process::IProcess>
    EventHandlerProcessFactory::createProcess(const process::ProcessOwner &owner,
                                              const std::string &name) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
      return std::make_unique<EventHandlerProcessImpl>(owner, name);
    }

    EventHandlerProcessImpl::EventHandlerProcessImpl(const process::ProcessOwner &owner,
                                                    const std::string &name)
        : m_owner(owner), m_process_id(-1), m_name(name),
          m_state(process::ProcessState::not_running),
          m_eventhandler(event::EventHandlerFactory().create()) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    EventHandlerProcessImpl::~EventHandlerProcessImpl() {}

    void EventHandlerProcessImpl::execute(int id) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::info) << logging::LOG_HEADER << "Executing process " << id << ": "
                          << m_name;
      m_process_id = id;
      update_state(process::ProcessState::running);

      m_eventhandler->start();

      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    void EventHandlerProcessImpl::kill() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;

      update_state(process::ProcessState::stopping);
      m_eventhandler->stop();
      update_state(process::ProcessState::finished);
      m_process_id = -1;

      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    process::ProcessState EventHandlerProcessImpl::get_state() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
      return m_state;
    }

    process::ProcessOwner EventHandlerProcessImpl::get_owner() {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
      return m_owner;
    }

    void EventHandlerProcessImpl::get_name(std::string &name) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      name = m_name;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }

    void EventHandlerProcessImpl::update_state(const process::ProcessState &state) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_START;
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      m_state = state;
      logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    }
  }
}