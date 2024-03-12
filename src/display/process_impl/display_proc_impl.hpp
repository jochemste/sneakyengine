#include "process.hpp"

#include <memory>
namespace display {
  namespace display_process {
    class DisplayProcessFactory {
      public:
        DisplayProcessFactory(){};

        std::unique_ptr<process::IProcess> createProcess(const process::ProcessOwner &owner,
                                                const std::string &name);
      };
  }
}