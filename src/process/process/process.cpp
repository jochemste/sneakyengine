#include "process.hpp"
#include "processmanager_fact_impl.hpp"

#include "logging.hpp"


namespace process {
  ProcessException::ProcessException(const char *message) : m_message(message) {}

  ProcessException::ProcessException(const std::string &message)
      : ProcessException(message.c_str()) {}

  const char *ProcessException::what() const noexcept { return m_message; }

  std::unique_ptr<IProcessManagerFactory> PROC_get_processmanager_factory() {
    return std::make_unique<ProcessManagerFactoryImpl>();
  }
} // namespace process
