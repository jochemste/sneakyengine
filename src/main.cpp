#include "engine.h"
#include "colour.h"
#include <iostream>

int main(int argc, char** argv){
  std::cout << "Starting test application" << std::endl;
  Red redclr;

  Engine engine;
  engine.openWindow(200,400);
  int res = engine.run();

  if(res){
    std::cout << "An error occurred" << std::endl;
  }

}
