#include "event.hpp"

#include "input.hpp"

class EventHandlerImpl : public event::IEventHandler {
public:
  EventHandlerImpl();
  virtual void start() override;
  virtual void stop() override;

private:
  std::unique_ptr<input::IInputPoller> m_inputpoller;
  bool m_stop;
};
