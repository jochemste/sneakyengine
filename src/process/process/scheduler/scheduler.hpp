#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <memory>

/// @brief Scheduler interface
template <typename T> class IScheduler {
public:
  /// @brief Get next scheduled process
  /// @return The next scheduled process
  virtual T &get_next() = 0;

  /// @brief Add process to scheduler
  /// @param[in] process The process to schedule
  /// @return integer with unique process id
  virtual int schedule(T &process, int priority = 0) = 0;

  /// @brief Get the number of running and waiting processes
  virtual unsigned int nr_processes() = 0;
};

/// @brief Abstract factory class to generate schedulers
template <typename T> class ISchedulerFactory {
public:
  /// @brief Create a first in first out scheduler
  virtual IScheduler<T> &createFIFOScheduler() = 0;
};

/// @brief Get the default scheduler factory implementation
template <typename T>
std::unique_ptr<ISchedulerFactory<T>> SCHED_get_scheduler_factory();

#endif // SCHEDULER_HPP
