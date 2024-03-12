#include "event_proc.hpp"

#include "event.hpp"
#include "logging.hpp"
#include "process.hpp"

#include <memory>
#include <mutex>

class EventHandlerProcessImpl : public IProcess {
public:
  EventHandlerProcessImpl() = delete;
  EventHandlerProcessImpl(const ProcessOwner &owner, const std::string &name);
  ~EventHandlerProcessImpl();

  virtual void execute(int id) override;
  virtual void kill() override;
  virtual ProcessState get_state() override;
  virtual ProcessOwner get_owner() override;
  virtual void get_name(std::string &name) override;

private:
  void update_state(const ProcessState &state);

  ProcessOwner m_owner;
  int m_process_id;
  std::string m_name;
  ProcessState m_state;
  std::unique_ptr<event::IEventHandler> m_eventhandler;
  std::mutex m_state_mutex;
};

std::unique_ptr<IProcess>
EventHandlerProcessFactory::createProcess(const ProcessOwner &owner,
                                          const std::string &name) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
  return std::make_unique<EventHandlerProcessImpl>(owner, name);
}

EventHandlerProcessImpl::EventHandlerProcessImpl(const ProcessOwner &owner,
                                                 const std::string &name)
    : m_owner(owner), m_process_id(-1), m_name(name),
      m_state(ProcessState::not_running),
      m_eventhandler(event::EventHandlerFactory().create()) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
}

EventHandlerProcessImpl::~EventHandlerProcessImpl() {}

void EventHandlerProcessImpl::execute(int id) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::info) << LOG_HEADER << "Executing process " << id << ": "
                      << m_name;
  m_process_id = id;
  update_state(ProcessState::running);

  m_eventhandler->start();

  Log(LogLevel::debug) << LOG_END;
}

void EventHandlerProcessImpl::kill() {
  Log(LogLevel::debug) << LOG_START;

  update_state(ProcessState::stopping);
  m_eventhandler->stop();
  update_state(ProcessState::finished);
  m_process_id = -1;

  Log(LogLevel::debug) << LOG_END;
}

ProcessState EventHandlerProcessImpl::get_state() {
  Log(LogLevel::debug) << LOG_START;
  const std::lock_guard<std::mutex> lock(m_state_mutex);
  Log(LogLevel::debug) << LOG_END;
  return m_state;
}

ProcessOwner EventHandlerProcessImpl::get_owner() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
  return m_owner;
}

void EventHandlerProcessImpl::get_name(std::string &name) {
  Log(LogLevel::debug) << LOG_START;
  name = m_name;
  Log(LogLevel::debug) << LOG_END;
}

void EventHandlerProcessImpl::update_state(const ProcessState &state) {
  Log(LogLevel::debug) << LOG_START;
  const std::lock_guard<std::mutex> lock(m_state_mutex);
  m_state = state;
  Log(LogLevel::debug) << LOG_END;
}
