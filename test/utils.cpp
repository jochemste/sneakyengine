#include "utils.hpp"

int getRandomInt() { return rand() % 500; }
int getRandomPositiveInt() { return ((rand() % 500) + 1) * 5; }

std::vector<Coordinates> *getRandomCoordVector() {
  int loop = getRandomPositiveInt();
  std::vector<Coordinates> *coordinates = new std::vector<Coordinates>;
  std::vector<int> x, y;

  for (int i = 0; i < loop; i++) {
    x.push_back(rand() % 1000000);
    y.push_back(rand() % 1000000);
    coordinates->push_back(Coordinates(x.at(i), y.at(i), -1));
  }

  return coordinates;
}

Coordinates getRandomCoordinates() {
  int x, y, z;
  x = getRandomInt();
  y = getRandomInt();
  z = getRandomInt();

  return Coordinates(x, y, z);
}
