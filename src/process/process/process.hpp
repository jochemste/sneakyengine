#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <memory>
#include <string>

/// Temporary C style function. Will be replaced by class
/// @return 0 when success, -1 when fail
int PROC_init();

/// Temporary C style function. Will be replaced by class
void PROC_quit();

/// State of IProcess
enum class ProcessState {
  /// Process is not running and was not started
  not_running,

  /// The process is running
  running,

  /// The process is being stopped
  stopping,

  /// The process has finished execution successfully
  finished,

  /// The process has finished and failed
  failed,
};

/// @brief Ownership enum class of process
enum class ProcessOwner {
  /// Owned by process manager. Modifier functions are disabled for others
  process_manager,

  /// Owned by client application. Client is responsible for execution
  client_application,

  /// No owner is defined
  none,
};

/// Interface to processes to be run. A variation of the command pattern
class IProcess {
public:
  /// Virtual destructor
  virtual ~IProcess() {}

  /// Start the process
  virtual void execute(int id) = 0;

  /// Stop the process
  virtual void kill() = 0;

  /// Get the current state of the process
  virtual ProcessState get_state() = 0;

  /// Get the current ownership of the process
  virtual ProcessOwner get_owner() = 0;

protected:
  /// Empty protected constructor
  IProcess() {}
  /// Constructor taking a process owner as parameter
  IProcess(const ProcessOwner & /*owner*/, const std::string & /*name*/) {}
};

/// @brief General process exception class
class ProcessException : public std::exception {
public:
  ProcessException(const char *message);
  ProcessException(const std::string &message);
  const char *what() const noexcept;

private:
  const char *m_message;
};

/// @brief Namespace for process module interfaces (currently unused)
namespace process {

/// @brief Interface to managing class of processes
/// Functions as adapter/proxy to scheduler classes
class IProcessManager {
public:
  virtual void start()                    = 0;
  virtual void stop()                     = 0;
  virtual void provide(IProcess &process) = 0;
  virtual bool busy()                     = 0;

protected:
  static const ProcessOwner m_ownership = ProcessOwner::process_manager;
};

/// @brief Abstract factory to Process Manager
class IProcessManagerFactory {
public:
  /// @brief Create a process manager
  virtual std::unique_ptr<IProcessManager> create_processmanager() = 0;
};

/// @brief Get a default process manager factory
std::unique_ptr<IProcessManagerFactory> PROC_get_processmanager_factory();

} // namespace process

#endif // PROCESS_HPP
