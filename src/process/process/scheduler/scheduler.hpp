#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <memory>
#include <mutex>
#include <queue>

namespace scheduler {

/// @brief Scheduler interface
template <class T> class IScheduler {
public:
  /// @brief Get next scheduled process
  /// @return The next scheduled process
  virtual T *get_next() = 0;

  /// @brief Add process to scheduler
  /// @param[in] process The process to schedule
  /// @return integer with unique process id
  virtual int schedule(T &process) = 0;

  /// @brief Add process to scheduler, with a provided priority
  /// @param[in] process The process to schedule
  /// @param[in] priority The priority to assign the process
  /// @return integer with unique process id
  virtual int schedule(T &process, int priority) = 0;

  /// @brief Get the number of running and waiting processes
  virtual unsigned int nr_processes() = 0;

protected:
};

/// @brief First In First Out implementation of IScheduler
/// This class does not clean up provided pointers at the moment
/// Stack based processes should remain in scope while the scheduler
/// is in scope, otherwise, they should be allocated and freed afterwards
/// This class is thread safe
template <class T> class FIFOScheduler : public IScheduler<T> {
public:
  FIFOScheduler() {}
  ~FIFOScheduler() {}

  virtual T *get_next() override {
    const std::lock_guard<std::mutex> lock(m_queue_mut);
    auto el = m_queue.front();
    m_queue.pop();
    return el;
  }
  virtual int schedule(T &process) override {
    return this->schedule(process, 0);
  }

  virtual int schedule(T &process, int /*priority*/) override {
    const std::lock_guard<std::mutex> lock(m_queue_mut);
    m_queue.push(&process);
    return 0;
  }
  virtual unsigned int nr_processes() override { return m_queue.size(); }

protected:
private:
  std::queue<T *> m_queue;
  std::mutex m_queue_mut;
};

} // namespace scheduler

#endif // SCHEDULER_HPP
