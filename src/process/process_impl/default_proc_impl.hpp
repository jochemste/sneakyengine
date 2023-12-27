#include "process.hpp"

#include <memory>

class DefaultProcessFactory {
public:
  DefaultProcessFactory(){};

  std::unique_ptr<IProcess> createProcess(const ProcessOwner &owner,
                                          const std::string &name);
};
