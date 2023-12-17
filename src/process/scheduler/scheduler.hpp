#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

/// Scheduler interface
template <typename T> class IScheduler {
public:
  /// Get next scheduled process
  virtual T &get_next() = 0;

  /// Add process to scheduler
  virtual void schedule(T &process, int priority = 0) = 0;

  /// Get the number of running and waiting processes
  virtual unsigned int nr_processes() = 0;
};

/// Abstract factory class to generate schedulers
template <typename T> class ISchedulerFactory {
public:
  virtual IScheduler<T> &createQueueScheduler() = 0;
};

#endif // SCHEDULER_HPP
