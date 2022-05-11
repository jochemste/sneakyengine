#include "gtest/gtest.h"

#include "../src/coordinates.hpp"

class CoordinatesTest : public ::testing::Test {
protected:
};

TEST_F(CoordinatesTest, InitWorks) {
  int one[3] = {1, 1, 1};
  int two[3] = {2, 3, 4};
  int three[3] = {-1000, 1023, -123};

  Coordinates c1(one[0], one[1], one[2]);
  Coordinates c2(two[0], two[1], two[2]);
  Coordinates c3(three[0], three[1], three[2]);

  EXPECT_EQ(one[0], c1.getX());
  EXPECT_EQ(one[1], c1.getY());
  EXPECT_EQ(one[2], c1.getZ());

  EXPECT_EQ(two[0], c2.getX());
  EXPECT_EQ(two[1], c2.getY());
  EXPECT_EQ(two[2], c2.getZ());

  EXPECT_EQ(three[0], c3.getX());
  EXPECT_EQ(three[1], c3.getY());
  EXPECT_EQ(three[2], c3.getZ());
}
