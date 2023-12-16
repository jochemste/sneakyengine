#ifndef PROCESS_HPP
#define PROCESS_HPP

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

  /// The process has finished execution successfully
  finished,

  /// The process has finished and failed
  failed,
};

/// Interface to processes to be run. A variation of the command pattern
class IProcess {
public:
  /// Start the process
  virtual void start(int id, const std::string &name) = 0;

  /// Stop the process
  virtual void stop() = 0;

  /// Get the current state of the process
  virtual ProcessState get_state() = 0;
};

/// Interface of Queue of processes
class IProcessQueue {
public:
  /// Push a process to the back of the queue
  virtual void push(IProcess &proc) = 0;

  /// Pop the process at the front of the queue
  virtual IProcess &pop() = 0;

  /// Get the size of the queue
  virtual unsigned int size() = 0;
};

/// Interface to managing class of processes
class IProcessManager {
public:
};

#endif // PROCESS_HPP
