#include "process.hpp"

#include <memory>

class EventHandlerProcessFactory {
public:
  EventHandlerProcessFactory(){};

  std::unique_ptr<IProcess> createProcess(const ProcessOwner &owner,
                                          const std::string &name);
};
