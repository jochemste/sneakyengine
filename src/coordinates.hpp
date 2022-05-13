#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <bits/stdc++.h>
#include <map>
#include <vector>

#include <iostream>

class Coordinates {
public:
  Coordinates(int, int, int);
  ~Coordinates();

  const int getX() const;
  const int getY() const;
  const int getZ() const;

  void setX(int x_);
  void setY(int y_);
  void setZ(int z_);

private:
  int x;
  int y;
  int z;
};

class CoordinateMap {
public:
  CoordinateMap();
  CoordinateMap(const std::vector<Coordinates> &coordinates);
  CoordinateMap(const CoordinateMap &other);
  ~CoordinateMap();

  void addCoordinates(const std::vector<Coordinates> &coordinates);
  std::vector<Coordinates> getCoordinates() const;

  const int size() const { return size_; };

  const int getMinX() const { return minX_; }
  const int getMinY() const { return minY_; }
  const int getMinZ() const { return minZ_; }
  const int getMaxX() const { return maxX_; }
  const int getMaxY() const { return maxY_; }
  const int getMaxZ() const { return maxZ_; }

  CoordinateMap &operator+=(const CoordinateMap &other);
  CoordinateMap &operator=(const CoordinateMap &other);
  CoordinateMap operator+(const CoordinateMap &other);
  // friend CoordinateMap operator+(CoordinateMap &lhs, const CoordinateMap
  // &rhs);

protected:
private:
  void clear();
  void sortMap();
  void rmDuplicates();
  void _setMinMaxXYZ(const int &x, const int &y, const int &z);

  std::map<int, std::vector<int>> *coordmap_; // Map of Y rows of X values
  int minX_, minY_, minZ_, maxX_, maxY_, maxZ_, size_;
};

#endif
