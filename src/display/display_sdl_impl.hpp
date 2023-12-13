#include "display.hpp"

class DisplaySDLImpl : public IDisplay {
public:
  virtual void start() override;
  virtual void stop() override;
};
