#include "coordinates_tst.hpp"
#include "utils.hpp"
#include <vector>

TEST_F(CoordinatesTest, TestInit) {
  int one[3] = {1, 1, 1};
  int two[3] = {2, 3, 4};
  int three[3] = {-1000, 1023, -123};

  Coordinates c1(one[0], one[1], one[2]);
  Coordinates c2(two[0], two[1], two[2]);
  Coordinates c3(three[0], three[1], three[2]);

  Coordinates c4 = c1;

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

  EXPECT_EQ(c1.getX(), c4.getX());
  EXPECT_EQ(c1.getY(), c4.getY());
  EXPECT_EQ(c1.getZ(), c4.getZ());
}

TEST_F(CoordinatesTest, TestSetX) {
  int x = 21;
  Coordinates c(x, 2, 3);

  EXPECT_EQ(x, c.getX());
  ASSERT_NE(x / 2, c.getX());
  c.setX(c.getX() * 12);
  EXPECT_EQ(x * 12, c.getX());
}

TEST_F(CoordinatesTest, TestSetY) {
  int y = 21;
  Coordinates c(5, y, 3);

  EXPECT_EQ(y, c.getY());
  ASSERT_NE(y / 2, c.getY());
  c.setY(c.getY() * 12);
  EXPECT_EQ(y * 12, c.getY());
}

TEST_F(CoordinatesTest, TestSetZ) {
  int z = 21;
  Coordinates c(2, 3, z);

  EXPECT_EQ(z, c.getZ());
  ASSERT_NE(z / 2, c.getZ());
  c.setZ(c.getZ() * 12);
  EXPECT_EQ(z * 12, c.getZ());
}

TEST_F(CoordinatesTest, TestPLUSIS) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  int x1, y1, z1;
  x1 = c1.getX();
  y1 = c1.getY();
  z1 = c1.getZ();

  int x2, y2, z2;
  x2 = c2.getX();
  y2 = c2.getY();
  z2 = c2.getZ();

  c1 += c2;

  EXPECT_EQ(c1.getX(), x1 + x2);
  EXPECT_EQ(c1.getY(), y1 + y2);
  EXPECT_EQ(c1.getZ(), z1 + z2);

  int n = getRandomInt();

  c2 += n;

  EXPECT_EQ(c2.getX(), x2 + n);
  EXPECT_EQ(c2.getY(), y2 + n);
  EXPECT_EQ(c2.getZ(), z2 + n);
}

TEST_F(CoordinatesTest, TestMINIS) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  int x1, y1, z1;
  x1 = c1.getX();
  y1 = c1.getY();
  z1 = c1.getZ();

  int x2, y2, z2;
  x2 = c2.getX();
  y2 = c2.getY();
  z2 = c2.getZ();

  c1 -= c2;

  EXPECT_EQ(c1.getX(), x1 - x2);
  EXPECT_EQ(c1.getY(), y1 - y2);
  EXPECT_EQ(c1.getZ(), z1 - z2);

  int n = getRandomInt();

  c2 -= n;

  EXPECT_EQ(c2.getX(), x2 - n);
  EXPECT_EQ(c2.getY(), y2 - n);
  EXPECT_EQ(c2.getZ(), z2 - n);
}

TEST_F(CoordinatesTest, TestPLUS) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  Coordinates c3 = c1 + c2;

  EXPECT_EQ(c3.getX(), c1.getX() + c2.getX());
  EXPECT_EQ(c3.getX(), c1.getX() + c2.getX());
  EXPECT_EQ(c3.getX(), c1.getX() + c2.getX());
}

TEST_F(CoordinatesTest, TestMIN) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  Coordinates c3 = c1 - c2;

  EXPECT_EQ(c3.getX(), c1.getX() - c2.getX());
  EXPECT_EQ(c3.getX(), c1.getX() - c2.getX());
  EXPECT_EQ(c3.getX(), c1.getX() - c2.getX());
}

TEST_F(CoordinatesTest, TestINCR) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  int x1, y1, z1;
  x1 = c1.getX();
  y1 = c1.getY();
  z1 = c1.getZ();

  int x2, y2, z2;
  x2 = c2.getX();
  y2 = c2.getY();
  z2 = c2.getZ();

  c1++;

  EXPECT_EQ(c1.getX(), x1 + 1);
  EXPECT_EQ(c1.getY(), y1 + 1);
  EXPECT_EQ(c1.getZ(), z1 + 1);

  int incr = getRandomInt();
  for (int i = 0; i < incr; i++)
    c2++;

  EXPECT_EQ(c2.getX(), x2 + incr);
  EXPECT_EQ(c2.getY(), y2 + incr);
  EXPECT_EQ(c2.getZ(), z2 + incr);
}

TEST_F(CoordinatesTest, TestDECR) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  int x1, y1, z1;
  x1 = c1.getX();
  y1 = c1.getY();
  z1 = c1.getZ();

  int x2, y2, z2;
  x2 = c2.getX();
  y2 = c2.getY();
  z2 = c2.getZ();

  c1--;

  EXPECT_EQ(c1.getX(), x1 - 1);
  EXPECT_EQ(c1.getY(), y1 - 1);
  EXPECT_EQ(c1.getZ(), z1 - 1);

  int incr = getRandomInt();
  for (int i = 0; i < incr; i++)
    c2--;

  EXPECT_EQ(c2.getX(), x2 - incr);
  EXPECT_EQ(c2.getY(), y2 - incr);
  EXPECT_EQ(c2.getZ(), z2 - incr);
}

TEST_F(CoordinatesTest, TestEQ) {
  Coordinates c1 = getRandomCoordinates();
  Coordinates c2 = getRandomCoordinates();

  if (c1.getX() == c2.getX() && c1.getY() == c2.getY() &&
      c1.getZ() == c2.getZ()) {
    EXPECT_EQ(c1 == c2, true);
  } else {
    EXPECT_EQ(c1 == c2, false);
  }
}

TEST_F(CoordinateMapTest, TestDefaultInit) {
  CoordinateMap c;
  EXPECT_EQ(-1, c.getMinX());
  EXPECT_EQ(-1, c.getMinY());
  EXPECT_EQ(-1, c.getMaxX());
  EXPECT_EQ(-1, c.getMaxY());
}

TEST_F(CoordinateMapTest, TestCoordInit) {
  int loop = getRandomPositiveInt();
  std::vector<Coordinates> *coordinates = new std::vector<Coordinates>;
  std::vector<int> x, y, z;

  for (int i = 0; i < loop; i++) {
    x.push_back(rand() % 1000000);
    y.push_back(rand() % 1000000);
    z.push_back(rand() % 1000000);
    coordinates->push_back(Coordinates(x.at(i), y.at(i), z.at(i)));
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
  int loop = getRandomPositiveInt();
  std::vector<Coordinates> *coordinates = new std::vector<Coordinates>;
  std::vector<int> x, y, z;

  for (int i = 0; i < loop; i++) {
    x.push_back(rand() % 1000000);
    y.push_back(rand() % 1000000);
    z.push_back(rand() % 1000000);
    coordinates->push_back(Coordinates(x.at(i), y.at(i), z.at(i)));
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
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  CoordinateMap cm2 = cm1;

  ASSERT_NE(&cm1, &cm2);

  EXPECT_EQ(cm1.size(), cm2.size());

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestAddCoordinates) {
  auto *c1 = getRandomCoordVector();

  CoordinateMap cm;
  cm.addCoordinates(*c1);

  EXPECT_EQ(c1->size(), cm.size());

  delete c1;
}

TEST_F(CoordinateMapTest, TestMove) {
  auto *c = getRandomCoordVector();

  CoordinateMap cm(*c);

  int minX, minY, maxX, maxY, x_add, y_add;
  for (int i = 0; i < 1000; i++) {
    x_add = getRandomInt();
    y_add = getRandomInt();
    minX = cm.getMinX();
    minY = cm.getMinY();
    maxX = cm.getMaxX();
    maxY = cm.getMaxY();

    cm.move(x_add, y_add);

    EXPECT_EQ(cm.getMinX(), minX + x_add);
    EXPECT_EQ(cm.getMinY(), minY + y_add);
    EXPECT_EQ(cm.getMaxX(), maxX + x_add);
    EXPECT_EQ(cm.getMaxY(), maxY + y_add);
  }

  delete c;
}

TEST_F(CoordinateMapTest, TestAdditionOperator) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

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

TEST_F(CoordinateMapTest, TestIndexOperator) {
  auto *c1 = getRandomCoordVector();

  CoordinateMap cm(*c1);

  int y1 = cm.end();
  int y2 = cm.atIndex(-1);
  int y3 = cm[-1];

  EXPECT_EQ(y1, y2);
  EXPECT_EQ(y1, y3);
  EXPECT_EQ(y2, y3);

  for (int i = 0; i < cm.size(); i++) {
    int n = rand() % cm.size();

    y1 = cm.atIndex(n);
    y2 = cm[n];
    EXPECT_EQ(y1, y2);
  }

  delete c1;
}

TEST_F(CoordinateMapTest, TestIsInMap) {
  auto *c1 = getRandomCoordVector();
  CoordinateMap cm(*c1);
  cm.rmDuplicates();

  // Check all current coordinates
  for (const auto &el : *c1) {
    EXPECT_EQ(true, cm.isInMap(el));
  }

  // Coordinate that exists
  Coordinates testC(c1->at(c1->size() - 1).getX(),
                    c1->at(c1->size() - 1).getY(), -1);
  EXPECT_EQ(true, cm.isInMap(testC));

  // X and Y value that exist in coordinate map
  int x = c1->at(c1->size() - 2).getX();
  int y = c1->at(c1->size() - 2).getY();
  EXPECT_EQ(true, cm.isInMap(x, y));

  // Coordinate that has non-existent X value and existing Y
  Coordinates testC2(cm.getMaxX() + 1, cm.getMaxY(), -1);
  EXPECT_EQ(false, cm.isInMap(testC2));

  // Coordinate that has existing X value and non-existent Y
  Coordinates testC3(cm.getMaxX(), cm.getMaxY() * 2, -1);
  EXPECT_EQ(false, cm.isInMap(testC3));

  // Negative values
  Coordinates testC4(-1, -1, -1);
  EXPECT_EQ(false, cm.isInMap(testC4));

  delete c1;
}

TEST_F(CoordinateMapTest, TestRmDuplicates) {
  auto *c1 = getRandomCoordVector();

  // Create duplicate Coordinate
  c1->push_back(c1->at(c1->size() - 1));

  CoordinateMap cm(*c1);
  // cm.size();

  cm.rmDuplicates();

  ASSERT_NE(cm.size(), c1->size());
  ASSERT_NE(cm.size(), 0);

  delete c1;
}

TEST_F(CoordinateMapTest, TestOperatorPLUSCoordinateMap) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  CoordinateMap cm2(*c2);
  cm1.rmDuplicates();
  cm2.rmDuplicates();

  CoordinateMap cm3 = cm1 + cm2;

  EXPECT_EQ(cm3.size(), cm1.size() + cm2.size());
  ASSERT_NE(cm3.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorPLUSISCoordinateMap) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  CoordinateMap cm2(*c2);
  cm1.rmDuplicates();
  cm2.rmDuplicates();

  int ogsize1 = cm1.size();
  int ogsize2 = cm2.size();

  cm1 += cm2;

  EXPECT_EQ(cm1.size(), ogsize1 + ogsize2);
  EXPECT_EQ(cm1.size() - ogsize2, ogsize1);
  EXPECT_EQ(cm2.size(), ogsize2);
  ASSERT_NE(cm1.size(), 0);
  ASSERT_NE(cm2.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorPLUSISCoordinates) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm(*c1);
  cm.rmDuplicates();

  int originalsize = cm.size();

  Coordinates coord(10, 10, -1);

  cm += coord;

  EXPECT_EQ(cm.size(), originalsize + 1);
  ASSERT_NE(cm.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorPLUSISCoordinateVector) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm(*c1);
  cm.rmDuplicates();

  int originalsize = cm.size();

  cm += *c2;

  EXPECT_EQ(cm.size(), originalsize + c2->size());
  ASSERT_NE(cm.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestEraseOne) {
  auto *c = getRandomCoordVector();

  CoordinateMap cm(*c);

  EXPECT_EQ(cm.isInMap(c->at(0)), true);

  cm.erase(c->at(0));

  EXPECT_EQ(cm.isInMap(c->at(0)), false);

  delete c;
}

TEST_F(CoordinateMapTest, TestEraseMulti) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm(*c1);
  cm += *c2;
  cm.rmDuplicates();

  for (auto &el : *c1)
    EXPECT_EQ(cm.isInMap(el), true);

  cm.erase(*c1);

  for (auto &el : *c1)
    EXPECT_EQ(cm.isInMap(el), false);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorMINISCoordinateMap) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  CoordinateMap cm2(*c2);
  cm1.rmDuplicates();
  cm2.rmDuplicates();

  int ogsize1 = cm1.size();
  int ogsize2 = cm2.size();

  cm1 -= cm2;

  EXPECT_EQ(cm1.size(), ogsize1);
  EXPECT_EQ(cm2.size(), ogsize2);
  ASSERT_NE(cm1.size(), 0);
  ASSERT_NE(cm2.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorMINISCoordinates) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm(*c1);
  cm.rmDuplicates();

  int originalsize = cm.size();

  Coordinates coord = c1->at(0);

  EXPECT_EQ(cm.isInMap(coord), true);

  cm -= coord;

  EXPECT_EQ(cm.isInMap(coord), false);

  EXPECT_EQ(cm.size(), originalsize - 1);
  ASSERT_NE(cm.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorMINISCoordinateVector) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm(*c1);
  cm.addCoordinates(*c2);

  int originalsize = cm.size();

  cm -= *c2;

  EXPECT_EQ(cm.size(), originalsize - c2->size());
  ASSERT_NE(cm.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorMINCoordinateMap) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  CoordinateMap cm2(*c2);
  cm1.rmDuplicates();
  cm2.rmDuplicates();

  CoordinateMap cm3 = cm1 - cm2;

  EXPECT_EQ(cm3.size() <= cm1.size(), true);
  ASSERT_NE(cm3.size(), 0);

  delete c1;
  delete c2;
}

TEST_F(CoordinateMapTest, TestOperatorMINCoordinates) {
  auto *c1 = getRandomCoordVector();
  auto *c2 = getRandomCoordVector();

  CoordinateMap cm1(*c1);
  std::cout << cm1.size() << std::endl;
  cm1 += *c2;
  std::cout << cm1.size() << std::endl;
  // cm1 -= *c2;
  std::cout << cm1.size() << std::endl;

  CoordinateMap cm3 = cm1 - *c1;
  std::cout << cm3.size() << " " << cm1.size() << " " << c1->size() << " "
            << c2->size() << std::endl;
  // std::cout << (cm1 - *c1).size() << std::endl;

  EXPECT_EQ(cm3.size(), cm1.size() - c2->size());
  ASSERT_NE(cm3.size(), 0);

  delete c1;
  delete c2;
}
