#include "shape_tst.hpp"

TEST_F(ShapeTest, TestEmptyInit) {
  Shape s;
  EXPECT_EQ(s.size(), 0);
}

TEST_F(ShapeTest, TestEmptyGetShape) {
  Shape s;
  auto coords = s.getShape();
  EXPECT_EQ(coords->size(), 0);
}
