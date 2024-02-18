#include "process.hpp"
#include "scheduler.hpp"
#include "threadpool.hpp"

#include <map>
#include <mutex>
#include <thread>
#include <vector>

/// @brief Internally used
namespace process_internal {
/// @brief Maximum number of threads.
/// @todo  To be replaced by configurable settings
constexpr int MAX_THREADS = 1;

class ProcessManagerImpl : public process::IProcessManager {
public:
  ProcessManagerImpl();
  ~ProcessManagerImpl();
  virtual void start() override;
  virtual void stop() override;
  virtual void provide(IProcess &process) override;
  virtual bool busy() override;

private:
  /// @brief Main run loop for process manager implementation. Is started as
  /// separate thread by start() and stopped by stop()
  void run_thread();

  /// @brief Clean processes from map. Only called from run_thread
  void clean();

  /// @brief Get a unique process ID
  int get_new_process_id();

  /// Scheduler of processes
  std::unique_ptr<scheduler::IScheduler<IProcess>> m_scheduler;

  /// Threadpool
  std::unique_ptr<threadpool::IThreadpool> m_threadpool;

  /// Maximum nr of threads in the threadpool
  const int m_max_threads = MAX_THREADS;

  /// Main running thread
  std::unique_ptr<std::thread> m_main_thread;

  // /// The processes currently running
  std::map<int, std::shared_ptr<IProcess>> m_processes;

  /// Boolean, indicating if process manager is running at the moment
  std::atomic<bool> m_is_running;

  /// The latest used ID. Incremented when requesting a new ID
  int m_latest_id;

  /// State mutex
  std::mutex m_state_mutex;
};
} // namespace process_internal
