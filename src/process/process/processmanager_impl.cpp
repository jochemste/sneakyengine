#include "processmanager_impl.hpp"

#include "logging.hpp"

#include <thread>

process_internal::ProcessManagerImpl::ProcessManagerImpl()
    : m_scheduler(std::make_unique<scheduler::FIFOScheduler<IProcess>>()),
      m_is_running(false), m_latest_id(0) {
  for (auto &el : m_processes) {
    el = nullptr;
  }
}
process_internal::ProcessManagerImpl::~ProcessManagerImpl() {}

void process_internal::ProcessManagerImpl::start() {
  Log(LogLevel::debug) << LOG_HEADER << "Starting main run thread";
  // start run as thread
  m_is_running  = true;
  m_main_thread = std::make_unique<std::thread>(
      &process_internal::ProcessManagerImpl::run, this);
}

void process_internal::ProcessManagerImpl::stop() {
  Log(LogLevel::debug) << LOG_HEADER << "Stopping main run thread";
  // Stop run loop
  // Send kill signal to running processes
  // Wait for processes to finish
  m_is_running = false;
  m_main_thread->join();
}

void process_internal::ProcessManagerImpl::provide(IProcess &process) {
  m_scheduler->schedule(process);
}

void process_internal::ProcessManagerImpl::run() {
  Log(LogLevel::debug) << LOG_HEADER << "Starting run";
  while (m_is_running) {
    // Check state of current processes and clean finished
    for (size_t index = 0; index < m_processes.size(); index++) {
      if ((m_processes.at(index) != nullptr) &&
          (m_processes.at(index)->get_state() == ProcessState::finished ||
           m_processes.at(index)->get_state() == ProcessState::failed)) {
        // Wait for process to properly finish and clean up thread
        wait_for_process(index);
        // Start a new process
        start_new_process(index);
      }
    }
  }
}

void process_internal::ProcessManagerImpl::wait_for_process(const int &index) {
  Log(LogLevel::debug) << LOG_HEADER << "Waiting for process to finish";
  m_threads.at(index)->join();
  m_threads.erase(index);
  Log(LogLevel::debug) << LOG_HEADER << "Process finished";
}

void process_internal::ProcessManagerImpl::start_new_process(const int &index) {
  Log(LogLevel::debug) << LOG_HEADER << "Starting new process";
  auto next_id                        = get_new_process_id();
  std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(
      &process_internal::ProcessManagerImpl::thread_execute_next, this, next_id,
      index);
  m_threads[next_id] = thread;
  Log(LogLevel::debug) << LOG_HEADER
                       << "New process started with PID: " << next_id;
}

int process_internal::ProcessManagerImpl::get_new_process_id() {
  Log(LogLevel::debug) << LOG_HEADER << "Getting new PID";
  m_latest_id = 0;
  // Loops until the id was not found
  while (m_threads.find(++m_latest_id) != m_threads.end())
    ;
  Log(LogLevel::debug) << LOG_HEADER << "New PID: " << m_latest_id;
  return m_latest_id;
}

void process_internal::ProcessManagerImpl::thread_execute_next(
    const int &id, const int &index) {
  auto next_process = std::shared_ptr<IProcess>(m_scheduler->get_next());
  if (m_processes.at(index)->get_state() != ProcessState::finished ||
      m_processes.at(index)->get_state() != ProcessState::failed) {
    /// @todo Log error, but execute anyway?
    Log(LogLevel::error)
        << LOG_HEADER << "Process with id " << id
        << " did not finish yet. This should never occur and indicates a bug "
           "in implementation of the processmanager";
  }
  m_processes[index] = next_process;
  next_process->execute(id);
}
