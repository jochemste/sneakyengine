#include "process.hpp"
#include "scheduler.hpp"

#include <map>
#include <mutex>
#include <thread>

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

private:
  /// @brief Main run loop for process manager implementation
  void run();

  void wait_for_process(const int &brief);

  /// @index Start a new process in a new thread
  void start_new_process(const int &index);

  /// @brief Get a unique process ID
  /// Currently a simple increment of m_latest_id
  int get_new_process_id();

  /// @brief Execute next process. Gets next process from scheduler
  void thr_execute_next(const int &id, const int &index);

  /// @brief Thread safe getter to check processmanager state
  bool get_is_running();

  /// Scheduler of processes
  std::unique_ptr<scheduler::IScheduler<IProcess>> m_scheduler;

  /// Main running thread
  std::unique_ptr<std::thread> m_main_thread;

  /// The pool of threads, mapped to process ID
  std::map<int, std::shared_ptr<std::thread>> m_threads;

  /// The processes currently running
  std::array<std::shared_ptr<IProcess>, MAX_THREADS> m_processes;

  /// Boolean, indicating if process manager is running at the moment
  std::atomic<bool> m_is_running;

  /// The latest used ID. Incremented when requesting a new ID
  int m_latest_id;

  /// State mutex
  std::mutex m_state_mutex;
};
} // namespace process_internal
