#include "scheduler.hpp"
#include "scheduler_fact_impl.hpp"

#include <memory>

template <typename T>
std::unique_ptr<ISchedulerFactory<T>> SCHED_get_scheduler_factory() {
  return std::make_shared<SchedulerFactoryImpl<T>>();
}
