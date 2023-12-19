#include "process.hpp"

#include <memory>

class DisplayProcessFactory {
public:
  DisplayProcessFactory(){};

  std::unique_ptr<IProcess> createProcess(const ProcessOwner &owner,
                                          const std::string &name);
};
