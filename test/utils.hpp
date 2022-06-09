#ifndef UTILS_HPP
#define UTILS_HPP

#include "../src/coordinates.hpp"

#include <time.h>
#include <vector>

void seedRand();
int getRandomInt();
int getRandomPositiveInt();
std::vector<Coordinates> *getRandomCoordVector();
Coordinates getRandomCoordinates();

#endif
