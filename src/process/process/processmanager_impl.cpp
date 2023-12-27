#include "processmanager_impl.hpp"

process_internal::ProcessManagerImpl::ProcessManagerImpl() {
  scheduler::FIFOScheduler<IProcess> f;
  // m_scheduler = std::make_unique<scheduler::FIFOScheduler<IProcess>>();
  // scheduler::SchedulerFactory<IProcess> sched_factory;
  // m_scheduler = sched_factory.createFIFOScheduler();
}
process_internal::ProcessManagerImpl::~ProcessManagerImpl() {}

void process_internal::ProcessManagerImpl::provide(IProcess &process) {}
