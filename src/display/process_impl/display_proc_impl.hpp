#include "process.hpp"

#include <memory>
namespace display {
  namespace displayProcess {
    class DisplayProcessFactory {
      public:
        DisplayProcessFactory(){};

        std::unique_ptr<IProcess> createProcess(const ProcessOwner &owner,
                                                const std::string &name);
      };
  }
}