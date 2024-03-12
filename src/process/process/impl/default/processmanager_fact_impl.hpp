#include "process.hpp"

#include <memory>

namespace process {
  /// @brief Process manager factory implementation
  class ProcessManagerFactoryImpl : public process::IProcessManagerFactory {
  public:
    virtual std::unique_ptr<process::IProcessManager>
    create_processmanager() override;
  };
}