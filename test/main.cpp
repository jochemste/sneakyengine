#include "gtest/gtest.h"

#include "coordinates_tst.hpp"
#include "shape_tst.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
