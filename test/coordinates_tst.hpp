#include "gtest/gtest.h"

#include "../src/coordinates.hpp"
#include "utils.hpp"

#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

class CoordinatesTest : public ::testing::Test {
protected:
  void SetUp() override { seedRand(); };
};

class CoordinateMapTest : public ::testing::Test {

protected:
  void SetUp() override { seedRand(); };
};

std::vector<Coordinates> *getRandomCoordVector();
