#include "processmanager_impl.hpp"

#include "logging.hpp"

#include <chrono>
#include <thread>

// PUBLIC

process_internal::ProcessManagerImpl::ProcessManagerImpl()
    : m_scheduler(std::make_unique<scheduler::FIFOScheduler<IProcess>>()),
      m_is_running(false), m_latest_id(0) {
  Log(LogLevel::debug) << LOG_START;
  for (auto &el : m_processes) {
    el = nullptr;
  }
  Log(LogLevel::debug) << LOG_END;
}
process_internal::ProcessManagerImpl::~ProcessManagerImpl() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::start() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Starting main run thread";
  // start run as thread
  {
    const std::lock_guard<std::mutex> lock(m_state_mutex);
    m_is_running = true;
  }
  m_main_thread = std::make_unique<std::thread>(
      &process_internal::ProcessManagerImpl::run, this);

  std::this_thread::sleep_for(std::chrono::seconds(1));
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::stop() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Stopping main run thread";
  // Stop run loop
  // Send kill signal to running processes
  // Wait for processes to finish
  // temporary debug delay
  std::this_thread::sleep_for(std::chrono::seconds(1));

  {
    const std::lock_guard<std::mutex> lock(m_state_mutex);
    m_is_running = false;
  }
  m_main_thread->join();
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::provide(IProcess &process) {
  Log(LogLevel::debug) << LOG_START;
  m_scheduler->schedule(process);
  Log(LogLevel::debug) << LOG_END;
}

// PRIVATE

void process_internal::ProcessManagerImpl::run() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Starting run";

  while (!stop_running()) {
    // Check state of current processes and clean finished
    for (size_t index = 0; index < m_processes.size(); index++) {
      if (m_processes.at(index) == nullptr) {
        Log(LogLevel::debug) << LOG_HEADER << "Starting first process";
        // Start a new process
        start_new_process(index);
      } else if (m_processes.at(index)->get_state() == ProcessState::finished ||
                 m_processes.at(index)->get_state() == ProcessState::failed) {
        Log(LogLevel::debug) << LOG_HEADER << "Waiting for a process to finish";
        // Wait for process to properly finish and clean up thread
        wait_for_process(index);
        Log(LogLevel::debug) << LOG_HEADER << "Starting a new process";
        // Start a new process
        start_new_process(index);
      }
    }
  }

  Log(LogLevel::debug) << LOG_HEADER << "Stop was called, killing processes";

  // Stop was called, kill all processes
  for (auto &proc : m_processes) {
    if (proc != nullptr) {
      proc->kill();
    }
  }
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::wait_for_process(const int &index) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Waiting for process to finish";
  m_threads.at(index)->join();
  m_threads.erase(index);
  Log(LogLevel::debug) << LOG_HEADER << "Process finished";
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::start_new_process(const int &index) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Starting new process";

  auto next_id = get_new_process_id();

  // Create new thread
  std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(
      &process_internal::ProcessManagerImpl::thr_execute_next, this, next_id,
      index);
  m_threads[next_id] = thread;

  // wait for process to start running
  while (m_processes.at(index) == nullptr ||
         m_processes.at(index)->get_state() == ProcessState::not_running) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    if (stop_running()) {
      Log(LogLevel::debug) << LOG_END;
      return;
    }
  }

  Log(LogLevel::debug) << LOG_HEADER
                       << "New process started with PID: " << next_id;
  Log(LogLevel::debug) << LOG_END;
}

void process_internal::ProcessManagerImpl::thr_execute_next(const int &id,
                                                            const int &index) {
  Log(LogLevel::debug) << LOG_START;
  std::shared_ptr<IProcess> next_process = nullptr;

  while (m_scheduler->nr_processes() <= 0) {
    if (stop_running()) {
      Log(LogLevel::debug) << LOG_END;
      return;
    }
    Log(LogLevel::debug) << LOG_HEADER << "Waiting "
                         << std::this_thread::get_id();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  Log(LogLevel::debug) << LOG_HEADER << "Finished waiting";
  next_process = std::shared_ptr<IProcess>(m_scheduler->get_next());

  if (m_processes.at(index) == nullptr) {
    Log(LogLevel::error) << LOG_HEADER << "Process is not initialised yet";
  } else if (m_processes.at(index)->get_state() != ProcessState::finished ||
             m_processes.at(index)->get_state() != ProcessState::failed) {
    /// @todo Log error, but execute anyway?
    Log(LogLevel::error)
        << LOG_HEADER << "Process with id " << id
        << " did not finish yet. This should never occur and indicates a bug "
           "in implementation of the processmanager";
  }
  m_processes[index] = next_process;
  next_process->execute(id);
  Log(LogLevel::debug) << LOG_END;
}

int process_internal::ProcessManagerImpl::get_new_process_id() {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_HEADER << "Getting new PID";
  m_latest_id = 0;

  // Loops until the id was not found
  while (m_threads.find(++m_latest_id) != m_threads.end())
    ;
  Log(LogLevel::debug) << LOG_HEADER << "New PID: " << m_latest_id;
  Log(LogLevel::debug) << LOG_END;
  return m_latest_id;
}

bool process_internal::ProcessManagerImpl::stop_running() {
  const std::lock_guard<std::mutex> lock(m_state_mutex);
  return !m_is_running;
}
