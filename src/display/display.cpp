#include "display.hpp"
#include "display_sdl_impl.hpp"

std::unique_ptr<IDisplay> DIS_get_display_instance() {
  return std::make_unique<DisplaySDLImpl>();
}
