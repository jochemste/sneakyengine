#include "engine.hpp"

#include <iostream>

int main(int argc, char **argv) {
  std::cout << "Starting test application" << std::endl;

  Engine engine;
  int res = engine.run();

  if (res) {
    std::cout << "An error occurred. Error code: " << res << std::endl;
  }
}
