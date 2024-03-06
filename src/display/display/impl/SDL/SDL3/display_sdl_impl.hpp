#include "display.hpp"

#include "SDL3/SDL.h"

/// State of DisplaySDLImpl, for internal use
enum class DisplayState { not_running, running, stopping, finished, failed };

class DisplaySDLImpl : public IDisplay {
public:
  DisplaySDLImpl();
  ~DisplaySDLImpl();

  virtual void start() override;
  virtual void stop() override;
  virtual void refresh() override;

private:
  /// @brief Wait to match framerate
  void wait_FPS();

  SDL_Window *m_window;
  SDL_Surface *m_surface;

  DisplayState m_state;

  const Uint64 m_tick_interval;

  Uint64 m_next_frame_tick_nr;
};
