#include "coordinates_tst.hpp"
#include <vector>

TEST_F(CoordinatesTest, InitWorks) {
  int one[3] = {1, 1, 1};
  int two[3] = {2, 3, 4};
  int three[3] = {-1000, 1023, -123};

  Coordinates c1(one[0], one[1], one[2]);
  Coordinates c2(two[0], two[1], two[2]);
  Coordinates c3(three[0], three[1], three[2]);

  // Test expected values
  EXPECT_EQ(one[0], c1.getX());
  EXPECT_EQ(one[1], c1.getY());
  EXPECT_EQ(one[2], c1.getZ());

  EXPECT_EQ(two[0], c2.getX());
  EXPECT_EQ(two[1], c2.getY());
  EXPECT_EQ(two[2], c2.getZ());

  EXPECT_EQ(three[0], c3.getX());
  EXPECT_EQ(three[1], c3.getY());
  EXPECT_EQ(three[2], c3.getZ());

  // Test unexpected values
  ASSERT_NE(one[0] + 1, c1.getX());
  ASSERT_NE(one[1] - 1, c1.getY());
  ASSERT_NE(one[2] * 2, c1.getZ());

  ASSERT_NE(two[0] + 10804, c2.getX());
  ASSERT_NE(two[1] - 64864, c2.getY());
  ASSERT_NE(two[2] * 35452, c2.getZ());

  ASSERT_NE(three[0] * 3542, c3.getX());
  ASSERT_NE(three[1] / 3, c3.getY());
  ASSERT_NE(three[2] * -1231, c3.getZ());
}

TEST_F(CoordinatesTest, SetXWorks) {
  int x = 21;
  Coordinates c(x, 2, 3);

  EXPECT_EQ(x, c.getX());
  ASSERT_NE(x / 2, c.getX());
  c.setX(c.getX() * 12);
  EXPECT_EQ(x * 12, c.getX());
}

TEST_F(CoordinatesTest, SetYWorks) {
  int y = 21;
  Coordinates c(5, y, 3);

  EXPECT_EQ(y, c.getY());
  ASSERT_NE(y / 2, c.getY());
  c.setY(c.getY() * 12);
  EXPECT_EQ(y * 12, c.getY());
}

TEST_F(CoordinatesTest, SetZWorks) {
  int z = 21;
  Coordinates c(2, 3, z);

  EXPECT_EQ(z, c.getZ());
  ASSERT_NE(z / 2, c.getZ());
  c.setZ(c.getZ() * 12);
  EXPECT_EQ(z * 12, c.getZ());
}

TEST_F(CoordinateMapTest, DefaultInitWorks) {
  CoordinateMap c;
  EXPECT_EQ(-1, c.getMinX());
  EXPECT_EQ(-1, c.getMinY());
  EXPECT_EQ(-1, c.getMaxX());
  EXPECT_EQ(-1, c.getMaxY());
}

TEST_F(CoordinateMapTest, CoordInitWorks) {
  int loop = rand() % 500;
  std::vector<Coordinates> *coordinates = new std::vector<Coordinates>;
  std::vector<int> x, y;

  for (int i = 0; i < loop; i++) {
    x.push_back(rand() % 1000000);
    y.push_back(rand() % 1000000);
    coordinates->push_back(Coordinates(x.at(i), y.at(i), -1));
  }

  sort(x.begin(), x.end());
  sort(y.begin(), y.end());

  // Insert unsorted vector of coordinates which are sorted in the constructor
  CoordinateMap cmap(*coordinates);

  EXPECT_EQ(x.at(0), cmap.getMinX());
  EXPECT_EQ(x.at(x.size() - 1), cmap.getMaxX());
  EXPECT_EQ(y.at(0), cmap.getMinY());
  EXPECT_EQ(y.at(y.size() - 1), cmap.getMaxY());

  delete coordinates;
}

TEST_F(CoordinateMapTest, CoordVectorsAreCopiedProperly) {
  int loop = rand() % 500;
  std::vector<Coordinates> *coordinates = new std::vector<Coordinates>;
  std::vector<int> x, y;

  for (int i = 0; i < loop; i++) {
    x.push_back(rand() % 1000000);
    y.push_back(rand() % 1000000);
    coordinates->push_back(Coordinates(x.at(i), y.at(i), -1));
  }

  // Insert unsorted vector of coordinates which are sorted in the constructor
  CoordinateMap cmap(*coordinates);

  ASSERT_NE(x.at(0), cmap.getMinX());
  ASSERT_NE(x.at(x.size() - 1), cmap.getMaxX());
  ASSERT_NE(y.at(0), cmap.getMinY());
  ASSERT_NE(y.at(y.size() - 1), cmap.getMaxY());

  delete coordinates;
}

TEST_F(CoordinateMapTest, TestCopyConstructor) {
  int loop;
  std::vector<Coordinates> *c1 = new std::vector<Coordinates>;
  std::vector<Coordinates> *c2 = new std::vector<Coordinates>;

  std::vector<int> x1, y1, x2, y2;

  loop = rand() % 500;
  for (int i = 0; i < loop; i++) {
    x1.push_back(rand() % 1000000);
    y1.push_back(rand() % 1000000);
    c1->push_back(Coordinates(x1.at(i), y1.at(i), -1));
  }

  CoordinateMap cm1(*c1);
  CoordinateMap cm2 = cm1;

  ASSERT_NE(&cm1, &cm2);

  EXPECT_EQ(cm1.size(), cm2.size());

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestAdditionOperator) {
  int loop;
  std::vector<Coordinates> *c1 = new std::vector<Coordinates>;
  std::vector<Coordinates> *c2 = new std::vector<Coordinates>;

  std::vector<int> x1, y1, x2, y2;

  loop = rand() % 500;
  for (int i = 0; i < loop; i++) {
    x1.push_back(rand() % 1000000);
    y1.push_back(rand() % 1000000);
    c1->push_back(Coordinates(x1.at(i), y1.at(i), -1));
  }

  loop = rand() % 500;
  for (int i = 0; i < loop; i++) {
    x2.push_back(rand() % 1000000);
    y2.push_back(rand() % 1000000);
    c2->push_back(Coordinates(x2.at(i), y2.at(i), -1));
  }

  CoordinateMap cm1(*c1);
  CoordinateMap cm2(*c2);

  EXPECT_EQ(c1->size(), cm1.size());
  EXPECT_EQ(c2->size(), cm2.size());

  int cm1_size = cm1.size();
  cm1 += cm2;
  EXPECT_EQ(cm1.size(), cm1_size + cm2.size());

  CoordinateMap cm3 = cm1 + cm2;
  EXPECT_EQ(cm3.size(), cm1.size() + cm2.size());

  int cm3_size = cm3.size();
  cm3 = cm1 + cm3;
  EXPECT_EQ(cm3.size(), cm1.size() + cm3_size);

  delete c1;
  delete c2;
}
