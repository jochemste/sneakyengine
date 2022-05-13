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

  int &operator[](const int &index);
  Coordinates &operator+=(const Coordinates &other);

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

  void setCoordinates(const std::vector<Coordinates> &coordinates);
  void addCoordinates(const std::vector<Coordinates> &coordinates);
  std::vector<Coordinates> getCoordinates() const;

  void move(Coordinates coord) { this->move(coord.getX(), coord.getX()); }
  void move(int x, int y);
  const int size() const { return size_; };
  std::vector<int> &at(const int &y) const;
  const int atIndex(const int &index) const;
  const int end() const;

  const bool isInMapY(const int y) const;
  const bool isInMap(const int x, const int y) const;
  const bool isInMap(const Coordinates &coord) const;

  const int getMinX() const { return minX_; }
  const int getMinY() const { return minY_; }
  const int getMinZ() const { return minZ_; }
  const int getMaxX() const { return maxX_; }
  const int getMaxY() const { return maxY_; }
  const int getMaxZ() const { return maxZ_; }

  void rmDuplicates();

  CoordinateMap &operator+=(const CoordinateMap &other);
  CoordinateMap &operator=(const CoordinateMap &other);
  CoordinateMap operator+(const CoordinateMap &other);
  const int operator[](const int &index) const;

protected:
private:
  void clear();
  void sortMap();
  void updateSize();
  void _setMinMaxXYZ(const int &x, const int &y, const int &z);

  std::map<int, std::vector<int>> *coordmap_; // Map of Y rows of X values
  int minX_, minY_, minZ_, maxX_, maxY_, maxZ_, size_;
  bool sorted_ = false;
};

#endif
