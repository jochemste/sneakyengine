#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <bits/stdc++.h>
#include <map>
#include <vector>

#include <iostream>
#include <sstream>

/// A class to handle coordinates. Allows a number of arithmetic operations for
/// easily handling and processing coordinates
class Coordinates {
public:
  Coordinates(int x_ = 0, int y_ = 0, int z_ = 0);
  Coordinates(const Coordinates &other);
  ~Coordinates();

  const int getX() const;
  const int getY() const;
  const int getZ() const;

  void setX(int x_);
  void setY(int y_);
  void setZ(int z_);

  int &operator[](const int &index);
  Coordinates &operator=(const Coordinates &other);
  bool operator==(const Coordinates &other);
  Coordinates &operator+=(const Coordinates &other);
  Coordinates &operator+=(const int n);
  Coordinates &operator++(int); // Postfix
  Coordinates &operator++();    // Prefix
  Coordinates &operator-=(const Coordinates &other);
  Coordinates &operator-=(const int n);
  Coordinates operator--(const int n); // Postfix
  Coordinates &operator--();           // Prefix
  Coordinates operator+(const Coordinates &rh);
  Coordinates operator-(const Coordinates &rh);
  operator std::string() const {
    std::stringstream ss;
    ss << "{" << x << ", " << y << ", " << z << "}";
    return ss.str();
  };

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

  void move(Coordinates coord) {
    this->move(coord.getX(), coord.getY(), coord.getZ());
  }
  void move(int x, int y, int z = -1);
  const int size() const { return size_; };
  std::vector<int> &at(const int &y) const;
  const int atIndex(const int &index) const;
  const int end() const;

  void erase(const Coordinates &coord, const bool updateSize = true);
  void erase(const std::vector<Coordinates> &coords);

  const bool isInMapY(const int y) const;
  const bool isInMap(const int x, const int y, const int z = -1) const;
  const bool isInMap(const Coordinates &coord) const;

  const int getMinX() const { return minX_; }
  const int getMinY() const { return minY_; }
  const int getMinZ() const { return minZ_; }
  const int getMaxX() const { return maxX_; }
  const int getMaxY() const { return maxY_; }
  const int getMaxZ() const { return maxZ_; }

  void rmDuplicates();
  void clean();

  CoordinateMap &operator+=(const CoordinateMap &other);
  CoordinateMap &operator+=(const Coordinates &coord);
  CoordinateMap &operator+=(const std::vector<Coordinates> &coords);
  CoordinateMap &operator-=(const CoordinateMap &other);
  CoordinateMap &operator-=(const Coordinates &coord);
  CoordinateMap &operator-=(const std::vector<Coordinates> &coords);
  CoordinateMap &operator=(const CoordinateMap &other);
  CoordinateMap operator+(const CoordinateMap &other);
  CoordinateMap operator+(const Coordinates &coord);
  CoordinateMap operator+(const std::vector<Coordinates> &coords);
  CoordinateMap operator-(const CoordinateMap &other);
  CoordinateMap operator-(const Coordinates &coord);
  CoordinateMap operator-(const std::vector<Coordinates> &coords);
  const int operator[](const int &index) const;

protected:
private:
  std::vector<int>::iterator findInY(const int x, const int y);
  void clear();
  void sortMap();
  void updateSize();
  void updateMinMax();
  void _setMinMaxXYZ(const int &x, const int &y, const int &z);

  std::map<int, std::vector<int>> *coordmap_; // Map of Y rows of X values
  int minX_, minY_, minZ_, maxX_, maxY_, maxZ_, size_;
  bool sorted_ = false;
};

#endif
