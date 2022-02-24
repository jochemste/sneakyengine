#ifndef ENGINE_H
#define ENGINE_H

#include "shape.hpp"
#include "coordinates.hpp"

#include <cmath>
#include <SDL.h>

enum class WindowState {
    OPEN,
    CLOSED
};

enum class EngineState {
    RUNNING,
    PAUSED,
    STOPPED,
    NOT_RUNNING
};

class Engine{
  
public:
    Engine();
    //Engine(int height_, int width_);
    ~Engine();

    int run();
    int stop();

    void openWindow(int height_, int width_);
    void closeWindow();
    
    void drawCircle(int center_x, int center_y, int radius);
    void drawShape(Shape& shape);
    
private:
    int height;
    int width;
    WindowState windowState = WindowState::CLOSED;
    EngineState engineState = EngineState::NOT_RUNNING;
    SDL_Renderer* renderer = NULL;
    //Uint8* red,green,blue,alpha = NULL;
    SDL_Window* window = NULL;
    
};

#endif
