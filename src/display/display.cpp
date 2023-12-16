#include "display.hpp"
#include "display_sdl_impl.hpp"

std::unique_ptr<IDisplay> DIS_get_display_instance() {
  return std::make_unique<DisplaySDLImpl>();
}

DisplayException::DisplayException(const char *message) : m_message(message) {}

DisplayException::DisplayException(const std::string &message)
    : DisplayException(message.c_str()) {}

const char *DisplayException::what() { return m_message; }
