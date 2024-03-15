#include "process.hpp"

#include <memory>

namespace process {
  /// @brief Process manager factory implementation
  class ProcessManagerFactoryImpl : public IProcessManagerFactory {
  public:
    virtual std::unique_ptr<IProcessManager>
    create_processmanager() override;
  };
}