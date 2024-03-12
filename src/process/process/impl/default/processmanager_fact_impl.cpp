#include "processmanager_fact_impl.hpp"
#include "processmanager_impl.hpp"

#include <memory>

namespace process {
  namespace default {
    std::unique_ptr<process::IProcessManager>
    ProcessManagerFactoryImpl::create_processmanager() {
      return std::make_unique<process_internal::ProcessManagerImpl>();
    }
  }
}