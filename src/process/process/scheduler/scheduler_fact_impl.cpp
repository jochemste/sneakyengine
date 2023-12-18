#include "scheduler_fact_impl.hpp"

template <typename T> SchedulerFactoryImpl<T>::SchedulerFactoryImpl() {}

template <typename T>
IScheduler<T> &SchedulerFactoryImpl<T>::createFIFOScheduler() {
  // allocate fifo scheduler with T as process type and return
}
