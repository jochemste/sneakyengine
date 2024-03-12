#include "eventhandler_impl.hpp"

EventHandlerImpl::EventHandlerImpl()
    : m_inputpoller(input::InputPollerFactory().create()), m_stop(false) {}

void EventHandlerImpl::start() {
  input::InputEvent event;
  while ((!m_stop) && (!(event == input::InputEvent::quit))) {
    m_inputpoller->poll(event);
  }
}

void EventHandlerImpl::stop() { m_stop = true; }
