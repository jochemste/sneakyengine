#include "threadpool_impl.hpp"

#include "logging.hpp"

namespace threadpool {
Threadpool_impl::Threadpool_impl()
    : Threadpool_impl(std::thread::hardware_concurrency()) {
  Log(LogLevel::debug) << LOG_START;
  Log(LogLevel::debug) << LOG_END;
}

Threadpool_impl::Threadpool_impl(int nr_threads)
    : m_nr_threads(nr_threads), m_nr_running(0), m_should_stop(false) {
  Log(LogLevel::debug) << LOG_START;

  Log(LogLevel::debug) << LOG_END;
}

void Threadpool_impl::start() {
  Log(LogLevel::debug) << LOG_START;

  for (int i = 0; i < m_nr_threads; i++) {
    m_threads.emplace_back(std::thread(&Threadpool_impl::thread_run, this));
  }

  Log(LogLevel::debug) << LOG_END;
}

void Threadpool_impl::stop() {
  Log(LogLevel::debug) << LOG_START;

  {
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    m_should_stop = true;
  }
  m_mutex_condition.notify_all();

  for (auto &thread : m_threads) {
    thread.join();
  }
  m_threads.clear();

  Log(LogLevel::debug) << LOG_END;
}

void Threadpool_impl::add_to_queue(const int &id,
                                   std::shared_ptr<IProcess> process) {
  Log(LogLevel::debug) << LOG_START;
  {
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    m_queue.push(std::make_pair(id, process));
  }
  m_mutex_condition.notify_one();

  Log(LogLevel::debug) << LOG_END;
}

int Threadpool_impl::get_nr_queued() {
  int nr_queued;
  {
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    nr_queued = m_queue.size();
  }
  return nr_queued;
}

int Threadpool_impl::get_nr_running() { return m_nr_running; }

bool Threadpool_impl::busy() {
  bool isbusy;
  {
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    isbusy = !m_queue.empty();
  }
  return isbusy;
}

void Threadpool_impl::thread_run() {
  Log(LogLevel::debug) << LOG_START;

  while (true) {
    int id = -1;
    std::shared_ptr<IProcess> process;

    {
      std::unique_lock<std::mutex> lock(m_queue_mutex);
      m_mutex_condition.wait(
          lock, [this] { return !m_queue.empty() || m_should_stop; });
      if (m_should_stop) {
        return;
      }

      Log(LogLevel::debug) << LOG_HEADER << "Getting id and process to execute";
      id      = m_queue.front().first;
      process = m_queue.front().second;
      m_queue.pop();
    }

    if ((process != nullptr)) {
      Log(LogLevel::debug) << LOG_HEADER << "Executing process with id " << id;
      m_nr_running++;
      process->execute(id);
      m_nr_running--;
    } else {
      Log(LogLevel::error) << LOG_HEADER << "Could not start process with id "
                           << id << ". Process is null or id is invalid";
    }
  }

  Log(LogLevel::debug) << LOG_END;
}

} // namespace threadpool
