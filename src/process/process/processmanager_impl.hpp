#include "process.hpp"
#include "scheduler.hpp"

namespace process_internal {
class ProcessManagerImpl : public process::IProcessManager {
public:
  ProcessManagerImpl();
  ~ProcessManagerImpl();
  virtual void provide(IProcess &process) override;

private:
  std::unique_ptr<scheduler::IScheduler<IProcess>> m_scheduler;
};
} // namespace process_internal
