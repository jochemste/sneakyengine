#ifndef THREADPOOL_IMPL_HPP
#define THREADPOOL_IMPL_HPP

#include "threadpool.hpp"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace threadpool {

///@brief Implementation of IThreadpool interface. Manages a pool of running
/// threads that will execute a process once this becomes available. Note, the
/// threads are always running after start() is called, and before stop() is
/// called
class Threadpool_impl : public IThreadpool {
public:
  /// @brief Constructor that sets the nr of threads to the maximum allowed nr
  /// for the hardware
  Threadpool_impl();

  /// @brief Constructor that sets the nr of threads to the specified nr
  Threadpool_impl(int nr_threads);

  Threadpool_impl(const Threadpool_impl &other) = delete;
  Threadpool_impl(Threadpool_impl &&other)      = default;

  ~Threadpool_impl() {}

  /// @brief Start the threads in the pool
  virtual void start() override;

  /// @brief Send the stop signal to all threads in the pool. Note, this does
  /// not send the kill signal to the processes, which should be done by the
  /// process owner
  virtual void stop() override;

  /// @brief Add a process with a specified id to the queue
  virtual void add_to_queue(const int &id,
                            std::shared_ptr<IProcess> process) override;

  /// @brief Get the nr of queued processes
  virtual int get_nr_queued() override;

  /// @brief Get the nr of running processes
  virtual int get_nr_running() override;

  /// @brief Returns true if processes are in the queue and/or processes are
  /// currently running
  virtual bool busy() override;

private:
  /// @brief Run loop for each thread
  void thread_run();

  /// @brief Fixed nr of threads to run in the pool
  const int m_nr_threads;

  /// @brief Nr of running processes
  std::atomic<int> m_nr_running;

  /// @brief Flag to indicate if the thread run loops should stop
  bool m_should_stop;

  /// @brief Mutex to protect queue access
  std::mutex m_queue_mutex;

  /// @brief Threads in the pool
  std::vector<std::thread> m_threads;

  /// @brief Conditional variable to help wait for new processes
  std::condition_variable m_mutex_condition;

  /// @brief Queue of processes and their identifiers
  std::queue<std::pair<int, std::shared_ptr<IProcess>>> m_queue;
};
} // namespace threadpool

#endif // THREADPOOL_IMPL_HPP
