#include "display.hpp"

#include "SDL3/SDL.h"

class DisplaySDLImpl : public IDisplay {
public:
  virtual void start() override;
  virtual void stop() override;

private:
  SDL_Window *m_window;
};
