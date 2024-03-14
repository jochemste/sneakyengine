#include "process.hpp"

#include <memory>

namespace input {
  namespace process_input {
    class EventHandlerProcessFactory {
    public:
      EventHandlerProcessFactory(){};

      std::unique_ptr<process::IProcess> createProcess(const process::ProcessOwner &owner,
                                                       const std::string &name);
    };
  }
}
