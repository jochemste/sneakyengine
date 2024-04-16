#ifndef EVENTHANDLER_IMPL_HPP
#define EVENTHANDLER_IMPL_HPP

#include "event.hpp"

#include "input.hpp"
namespace input {
  namespace event {
    class EventHandlerImpl : public event::IEventHandler {
    public:
      EventHandlerImpl();
      virtual void start() override;
      virtual void stop() override;

    private:
      std::unique_ptr<input::IInputPoller> m_inputpoller;
      bool m_stop;
    };
  }
}

#endif // EVENTHANDLER_IMPL_HPP
