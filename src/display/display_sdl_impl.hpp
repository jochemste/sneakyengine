#include "display.hpp"

#include "SDL3/SDL.h"

class DisplaySDLImpl : public IDisplay {
public:
  DisplaySDLImpl();
  ~DisplaySDLImpl();

  virtual void start() override;
  virtual void stop() override;
  virtual void refresh() override;

private:
  /// @brief Wait to match framerate
  void waitFPS();

  SDL_Window *m_window;
  SDL_Surface *m_surface;

  const Uint32 m_tick_interval;

  Uint32 m_next_frame_tick_nr;
};
