#include "coordinates.hpp"

Coordinates::Coordinates(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
Coordinates::~Coordinates() {}

const int Coordinates::getX() const { return x; }
const int Coordinates::getY() const { return y; }
const int Coordinates::getZ() const { return z; }

void Coordinates::setX(int x_) { x = x_; }
void Coordinates::setY(int y_) { y = y_; }
void Coordinates::setZ(int z_) { z = z_; }

CoordinateMap::CoordinateMap()
    : coordmap_(new std::map<int, std::vector<int>>), minX_(-1), minY_(-1),
      maxX_(-1), maxY_(-1), size_(0) {}

CoordinateMap::CoordinateMap(const std::vector<Coordinates> &coordinates)
    : CoordinateMap() {
  this->addCoordinates(coordinates);
}

CoordinateMap::CoordinateMap(const CoordinateMap &other) : CoordinateMap() {
  this->clear();
  size_ = 0;
  this->addCoordinates(other.getCoordinates());
}

CoordinateMap::~CoordinateMap() { delete coordmap_; }

void CoordinateMap::addCoordinates(
    const std::vector<Coordinates> &coordinates) {

  for (const auto &el : coordinates) {
    if (coordmap_->find(el.getY()) == coordmap_->end()) {
      // If Y is not found as key in the map, insert the key (Y) with the first
      // X value
      coordmap_->insert(
          std::pair<int, std::vector<int>>(el.getY(), {el.getX()}));
    } else {
      // If Y is found as key in the map, append the X to the vector
      coordmap_->at(el.getY()).push_back(el.getX());
    }

    size_++;
    this->_setMinMaxXYZ(el.getX(), el.getY(), el.getZ());
  }

  this->sortMap();
}

std::vector<Coordinates> CoordinateMap::getCoordinates() const {
  std::vector<Coordinates> coordinates;

  for (const auto &el : *coordmap_) {
    for (const auto &x : el.second) {
      coordinates.push_back(Coordinates(el.first, x, -1));
    }
  }

  return coordinates;
}

CoordinateMap &CoordinateMap::operator+=(const CoordinateMap &other) {
  this->addCoordinates(other.getCoordinates());
  return *this;
}

CoordinateMap &CoordinateMap::operator=(const CoordinateMap &other) {
  this->clear();
  this->addCoordinates(other.getCoordinates());
  return *this;
}

CoordinateMap CoordinateMap::operator+(const CoordinateMap &other) {
  CoordinateMap c(this->getCoordinates());
  c.addCoordinates(other.getCoordinates());
  return c;
}

void CoordinateMap::clear() {
  coordmap_->clear();
  minX_ = -1;
  minY_ = -1;
  maxX_ = -1;
  maxY_ = -1;
  size_ = 0;
}

/// Sort the vectors in the map
void CoordinateMap::sortMap() {
  for (auto &el : *coordmap_) {
    sort(el.second.begin(), el.second.end());
  }
}

void CoordinateMap::rmDuplicates() {}

/// Compare the provided coordinates with the member min/max X/Y to determine
/// the minimum and maximum values
void CoordinateMap::_setMinMaxXYZ(const int &x, const int &y, const int &z) {
  switch (minX_) {
  case -1:
    minX_ = x;
    break;
  default:
    if (minX_ > x) {
      minX_ = x;
    }
  }

  switch (minY_) {
  case -1:
    minY_ = y;
    break;
  default:
    if (minY_ > y) {
      minY_ = y;
    }
  }

  switch (minZ_) {
  case -1:
    minZ_ = z;
    break;
  default:
    if (minZ_ > z) {
      minZ_ = z;
    }
  }

  switch (maxX_) {
  case -1:
    maxX_ = x;
    break;
  default:
    if (maxX_ < x) {
      maxX_ = x;
    }
  }

  switch (maxY_) {
  case -1:
    maxY_ = y;
    break;
  default:
    if (maxY_ < y) {
      maxY_ = y;
    }
  }

  switch (maxZ_) {
  case -1:
    maxZ_ = z;
    break;
  default:
    if (maxZ_ < z) {
      maxZ_ = z;
    }
  }
}
