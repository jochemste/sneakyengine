#include "engine.h"
#include <iostream>

/*
Engine::Engine(int height_, int width_): height(height_), width(width_){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
*/
Engine::Engine(){}

Engine::~Engine(){
    if (this->engineState==EngineState::RUNNING){
	stop();
	//closeWindow();
	//SDL_Quit();
	//this->engineState = EngineState::STOPPED;
    }
}

int Engine::run(){
    SDL_Log("Starting run loop");
    SDL_Event event;

    int x=20;
    int y=10;
    int r=50;

    Circle circle(x, y, r);
    Rectangle rect(x+r, y, 20, 30);
    while(!(event.type == SDL_QUIT)){
	SDL_RenderClear(renderer);
	SDL_Delay(10);
	SDL_PollEvent(&event);
	drawShape(circle);
	drawShape(rect);
	//circle.move(1,1);
	
	SDL_RenderPresent(renderer);
    }

    return 0;
}

int Engine::stop(){
    closeWindow();
    SDL_Quit();
    this->engineState = EngineState::STOPPED;
    return 0;
}

void Engine::openWindow(int height_, int width_){
    SDL_DisplayMode dm;
    //SDL_GetDesktopDisplayMode(0, &dm);
    //height=dm.h;
    //width=dm.w;
    //std::cout <<height << " " << width << std::endl;
    //if (height==0){height=height_;}
    //if (width==0){width=width_;}
    height=height_;
    width=width_;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    windowState = WindowState::OPEN;
}

void Engine::closeWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    windowState = WindowState::CLOSED;
}

// @brief Render a shape
void Engine::drawShape(Shape& shape){
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(renderer, &r,&g,&b,&a);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Get coordinates to draw and render the coordinates as points
    for(auto& el: *shape.getShape()){
	SDL_RenderDrawPoint(renderer, el.getX(), el.getY());
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
