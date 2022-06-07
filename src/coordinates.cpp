#include "coordinates.hpp"
#include <vector>

Coordinates::Coordinates(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
Coordinates::~Coordinates() {}

const int Coordinates::getX() const { return x; }
const int Coordinates::getY() const { return y; }
const int Coordinates::getZ() const { return z; }

void Coordinates::setX(int x_) { x = x_; }
void Coordinates::setY(int y_) { y = y_; }
void Coordinates::setZ(int z_) { z = z_; }

int &Coordinates::operator[](const int &index) {
  switch (index) {
  case 0:
    return x;
    break;
  case 1:
    return y;
    break;
  case 2:
    return z;
    break;
  default:
    return x;
  }
}

Coordinates &Coordinates::operator+=(const Coordinates &other) {
  this->x += other.getX();
  this->y += other.getY();
  return *this;
}

CoordinateMap::CoordinateMap()
    : coordmap_(new std::map<int, std::vector<int>>), minX_(-1), minY_(-1),
      maxX_(-1), maxY_(-1), size_(0) {}

CoordinateMap::CoordinateMap(const std::vector<Coordinates> &coordinates)
    : CoordinateMap() {
  this->addCoordinates(coordinates);
}

CoordinateMap::CoordinateMap(const CoordinateMap &other) : CoordinateMap() {
  this->clear();
  this->addCoordinates(other.getCoordinates());
}

CoordinateMap::~CoordinateMap() { delete coordmap_; }

void CoordinateMap::setCoordinates(
    const std::vector<Coordinates> &coordinates) {
  this->clear();
  this->addCoordinates(coordinates);
}

void CoordinateMap::addCoordinates(
    const std::vector<Coordinates> &coordinates) {
  // Set sorted_ to false if coordinates are available, so map will be sorted
  // once coordinates are added
  if (coordinates.size() > 0)
    sorted_ = false;

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

    // size_++;
    this->_setMinMaxXYZ(el.getX(), el.getY(), el.getZ());
  }
  this->updateSize();
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

void CoordinateMap::move(int x, int y) {
  // auto newMap = *coordmap_;
  auto coords = this->getCoordinates();
  this->clear();

  for (auto &el : coords) {
    el += Coordinates(x, y, -1);
    // el.setX(el.getX() + x);
    // el.setY(el.getY() + y);
  }

  this->setCoordinates(coords);
}

/// Access vectors of X values by reference of Y values.
/// @param y Reference to a Y value, used to indicate a row of X values.
std::vector<int> &CoordinateMap::at(const int &y) const {
  if (coordmap_->find(y) != coordmap_->end()) {
    return coordmap_->at(y);
  } else {
    return (--coordmap_->end())->second;
  }
}

/// Access rows in the coordinate map. Allows out of bounds indexes, by
/// performing modulus operations on it to always ensure the index is within
/// range. Negative indexes are also allowed, where -1 will access the last
/// element for example
/// @param index Reference to the index value, used to specify the index of the
/// row (not the actual Y value which can be gotten with this->at(y))
const int CoordinateMap::atIndex(const int &index) const {
  int i = index; // Since index is constant, copy it

  // Ensure that negative values are counting back from end of map
  while (i < 0 || i >= this->size()) {
    if (i < 0)
      i *= -1;
    i = this->size() - i;
  }

  // Ensure i is within range by performing modulus operation using the size
  // of the coordmap
  if (i >= this->size())
    i %= this->size();

  int ctr = 0;
  for (std::map<int, std::vector<int>>::iterator it = coordmap_->begin();
       it != coordmap_->end(); ++it) {
    if (ctr++ == i)
      return it->first;
  }

  return -1;
}

const int CoordinateMap::end() const {
  std::map<int, std::vector<int>>::iterator it = --coordmap_->end();
  return it->first;
}

void CoordinateMap::erase(const Coordinates &coord) {
  if (this->isInMap(coord)) {
    auto it = this->findInY(coord.getX(), coord.getY());
    if (it != coordmap_->at(coord.getY()).end())
      coordmap_->at(coord.getY()).erase(it);
  }
}

const bool CoordinateMap::isInMapY(const int y) const {
  return (coordmap_->find(y) != coordmap_->end());
}

const bool CoordinateMap::isInMap(const int x, const int y, const int z) const {
  return this->isInMap(Coordinates(x, y, z));
}

const bool CoordinateMap::isInMap(const Coordinates &coord) const {
  std::vector<int> xRow;
  if (this->isInMapY(coord.getY())) {
    xRow = this->at(coord.getY());
  } else {
    return false;
  }

  for (const auto &el : xRow) {
    if (el == coord.getX()) {
      return true;
    }
  }

  return false;
}

CoordinateMap &CoordinateMap::operator+=(const CoordinateMap &other) {
  this->addCoordinates(other.getCoordinates());
  return *this;
}

CoordinateMap &CoordinateMap::operator+=(const Coordinates &coord) {
  std::vector<Coordinates> c;
  c.push_back(coord);
  this->addCoordinates(c);
  return *this;
}

CoordinateMap &
CoordinateMap::operator+=(const std::vector<Coordinates> &coords) {
  this->addCoordinates(coords);
  return *this;
}

CoordinateMap &CoordinateMap::operator=(const CoordinateMap &other) {
  this->clear();
  this->addCoordinates(other.getCoordinates());
  return *this;
}

CoordinateMap CoordinateMap::operator+(const CoordinateMap &other) {
  CoordinateMap cm(this->getCoordinates());
  cm.addCoordinates(other.getCoordinates());
  return cm;
}

CoordinateMap CoordinateMap::operator+(const Coordinates &coord) {
  CoordinateMap cm(this->getCoordinates());
  std::vector<Coordinates> c1;
  c1.push_back(coord);
  cm.addCoordinates(c1);
  return cm;
}
CoordinateMap CoordinateMap::operator+(const std::vector<Coordinates> &coords) {
  CoordinateMap cm(this->getCoordinates());
  cm.addCoordinates(coords);
  return cm;
}

/// Allow access to the elements of the coordinate map. Returns a row at the
/// provided Y value
const int CoordinateMap::operator[](const int &index) const {
  return this->atIndex(index);
}

std::vector<int>::iterator CoordinateMap::findInY(const int x, const int y) {
  if (this->isInMapY(y)) {
    int findX = x;
    int i = 0;
    for (auto it = coordmap_->at(y).begin(); it != coordmap_->at(y).end();
         ++it, i++) {
      if (coordmap_->at(y).at(i) == findX)
        return it;
    }
  }

  return coordmap_->at(y).end();
}

/// Clear the coordinate map and reset min/max values and the size counter
void CoordinateMap::clear() {
  coordmap_->clear();
  minX_ = -1;
  minY_ = -1;
  maxX_ = -1;
  maxY_ = -1;
  size_ = 0;
  sorted_ = false;
}

/// Sort the vectors in the map
void CoordinateMap::sortMap() {
  for (auto &el : *coordmap_) {
    sort(el.second.begin(), el.second.end());
  }
  sorted_ = true;
}

void CoordinateMap::rmDuplicates() {
  if (!sorted_)
    this->sortMap();

  // Loop through map
  for (auto it = coordmap_->begin(); it != coordmap_->end(); it++) {
    int s = it->second.size();
    std::vector<int> newRow;
    for (auto i = 0; i < it->second.size(); ++i) {
      if (((i + 1) == it->second.size()) ||
          (it->second.at(i) != it->second.at(i + 1))) {
        newRow.push_back(it->second.at(i));
      }
    }
    it->second = newRow;
  }

  this->updateSize();
}

void CoordinateMap::updateSize() {
  size_ = 0;
  for (const auto &el : *coordmap_) {
    size_ += el.second.size();
  }
}

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
