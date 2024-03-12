#include "processmanager_impl.hpp"

#include "logging.hpp"

#include <chrono>
#include <thread>

namespace process {
  // PUBLIC

  process_internal::ProcessManagerImpl::ProcessManagerImpl()
      : m_scheduler(std::make_unique<scheduler::FIFOScheduler<IProcess>>()),
        m_is_running(false), m_latest_id(0) {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;

    threadpool::ThreadpoolFactory tpfact;
    m_threadpool = tpfact.create();

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  process_internal::ProcessManagerImpl::~ProcessManagerImpl() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    if (m_processes.size()) {
      m_processes.clear();
    }
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void process_internal::ProcessManagerImpl::start() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    m_threadpool->start();

    // Start run loop as thread
    {
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      m_is_running = true;
    }
    m_main_thread = std::make_unique<std::thread>(
        &process_internal::ProcessManagerImpl::run_thread, this);

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void process_internal::ProcessManagerImpl::stop() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;

    // Stop run thread and send kill signal
    {
      const std::lock_guard<std::mutex> lock(m_state_mutex);
      m_is_running = false;
    }

    // Wait for run loop to finish
    m_main_thread->join();

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void process_internal::ProcessManagerImpl::provide(IProcess &process) {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    m_scheduler->schedule(process);
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  bool process_internal::ProcessManagerImpl::busy() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    return (m_processes.size() > 0);
  }

  // PRIVATE

  void process_internal::ProcessManagerImpl::run_thread() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Starting run";

    while (m_is_running) {

      // Add new process to threadpool if possible
      if (m_threadpool->get_nr_queued() <= m_max_threads &&
          m_scheduler->nr_processes() > 0) {

        // Create new process in map
        auto new_id         = get_new_process_id();
        m_processes[new_id] = std::shared_ptr<IProcess>(m_scheduler->get_next());

        // add to queue
        m_threadpool->add_to_queue(new_id, m_processes.at(new_id));
      }

      // clean finished or failed processes
      clean();
    }

    logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Stop was called, killing processes";

    // Stop was called, kill all processes
    for (auto &[id, proc] : m_processes) {
      logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Killing process with PID " << id;
      proc->kill();
    }

    // Stop thread pool threads
    logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Waiting for threadpool to stop";
    m_threadpool->stop();

    while (m_threadpool->busy()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  void process_internal::ProcessManagerImpl::clean() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;

    // determine which processes to clean
    std::vector<int> to_clean;
    for (auto &[id, proc] : m_processes) {
      if (proc->get_state() == ProcessState::finished) {
        logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Cleaning finished process " << id;
        to_clean.push_back(id);
      } else if (proc->get_state() == ProcessState::failed) {
        logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Cleaning failed process " << id;
        to_clean.push_back(id);
      }
    }

    // Cleanup finished processes
    for (const auto &id : to_clean) {
      m_processes.erase(id);
    }

    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
  }

  int process_internal::ProcessManagerImpl::get_new_process_id() {
    logging::Log(logging::LogLevel::debug) << logging::LOG_START;
    logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "Getting new PID";
    m_latest_id = 0;

    // Loops until the id was not found
    while (m_processes.find(++m_latest_id) != m_processes.end())
      ;
    logging::Log(logging::LogLevel::debug) << logging::LOG_HEADER << "New PID: " << m_latest_id;
    logging::Log(logging::LogLevel::debug) << logging::LOG_END;
    return m_latest_id;
  }
  
}