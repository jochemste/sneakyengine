#ifndef SCHEDULER_FACT_IMPL_HPP
#define SCHEDULER_FACT_IMPL_HPP

#include "scheduler.hpp"

template <typename T> class SchedulerFactoryImpl {
  SchedulerFactoryImpl();
  virtual IScheduler<T> &createFIFOScheduler() override;
};

#endif // SCHEDULER_FACT_IMPL_HPP
