#include "shape_tst.hpp"
#include "utils.hpp"

TEST_F(ShapeTest, DefaultConstructorWorks) {
  Shape s;
  EXPECT_EQ(s.size(), 0);
}

TEST_F(ShapeTest, EmptyGetShapeWorks) {
  Shape s;
  auto coords = s.getShape();
  EXPECT_EQ(coords->size(), 0);
}

TEST_F(ShapeTest, GetIdWorks) {
  std::string id = "test";
  Shape s(id);

  EXPECT_EQ(id, s.getId());
}

TEST_F(ShapeTest, MoveWorks) {
  auto *c = getRandomCoordVector();
  CoordinateMap *cm = new CoordinateMap(*c);
  Shape s(cm, "test");

  int maxX1, maxX2, maxY1, maxY2, minX1, minX2, minY1, minY2;

  maxX1 = s.getMap()->getMaxX();
  maxY1 = s.getMap()->getMaxY();
  minX1 = s.getMap()->getMinX();
  minY1 = s.getMap()->getMinY();

  int mx, my;
  mx = getRandomPositiveInt();
  my = getRandomPositiveInt();

  s.move(mx, my);

  maxX2 = s.getMap()->getMaxX();
  maxY2 = s.getMap()->getMaxY();
  minX2 = s.getMap()->getMinX();
  minY2 = s.getMap()->getMinY();

  ASSERT_NE(maxX1, maxX2);
  ASSERT_NE(maxY1, maxY2);
  ASSERT_NE(minX1, minX2);
  ASSERT_NE(minY1, minY2);

  EXPECT_EQ(maxX2, maxX1 + mx);
  EXPECT_EQ(maxY2, maxY1 + my);
  EXPECT_EQ(minX2, minX1 + mx);
  EXPECT_EQ(minY2, minY1 + my);

  delete c;
}

TEST_F(ShapeTest, GetShapeWorks) {
  auto *c1 = getRandomCoordVector();
  CoordinateMap cm(c1);

  delete c1;
}

TEST_F(CircleTest, OverlapWorks) {
  Circle c1(100, 100, 20);
  Circle c2(150, 150, 20);  // Does not overlap
  Circle c3(110, 110, 100); // Should overlap

  EXPECT_FALSE(c1.overlaps(c2));
  EXPECT_TRUE(c1.overlaps(c3));
}
