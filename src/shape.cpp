#include "shape.hpp"
#include "coordinates.hpp"

#include <iostream>

/// Default constructor
/// @param id Sets the id of the Shape, to be able to easily identify a shape,
/// for example a Circle would get id="circle"
Shape::Shape(const std::string id) : id_(id), coordsUpToDate(false) {
  coordinates = new std::vector<Coordinates>;
  coordmap_ = new CoordinateMap;
}

/// Default constructor
/// @param cm Pointer to coordinatemap to create a custom shape
/// @param id Sets the id of the Shape, to be able to easily identify a shape,
/// for example a Circle would get id="circle"
Shape::Shape(CoordinateMap *cm, const std::string id)
    : id_(id), coordsUpToDate(false) {
  coordinates = new std::vector<Coordinates>;
  coordmap_ = cm;
  coordmap_->rmDuplicates();
  *coordinates = coordmap_->getCoordinates();
  coordsUpToDate = true;
}

/// Default destructor
Shape::~Shape() {
  delete coordinates;
  delete coordmap_;
}

/// Move the shape by incrementing all the x coordinates by the provided x_ and
/// the y by the provided y_
/// @param x_ X value to increment all X values in the coordinate vector with
/// @param y_ Y value to increment all Y values in the coordinate vector with
void Shape::move(int x_, int y_) {
  coordmap_->move(Coordinates(x_, y_, 0));
  *coordinates = coordmap_->getCoordinates();
  coordsUpToDate = true;
}

/// Check if two shapes overlap with each other. Virtual member function, to
/// allow better checking for shapes such as circles, which can be calculated
/// quickly.
/// @param other Pointer to another shape
bool Shape::overlaps(Shape &other) {
  if ((this->size() == 0) || (other.size() == 0))
    return false;

  // If left most X is further to the right than other right most X, they do not
  // overlap or vice versa. The same goes for Y coordinates, although right/left
  // should be replaced by lower/higher
  if ((this->getMinX() > other.getMaxX()) ||
      (this->getMaxX() < other.getMinX()) ||
      (this->getMinY() > other.getMaxY()) ||
      (this->getMaxY() < other.getMinY())) {
    return false;
  }

  auto *coords = new std::vector<Coordinates>;
  other.getShape(*coords);

  for (const auto &el : *coords) {
    if (coordmap_->isInMap(el))
      return true;
  }

  return false;
}

/// Get the shape as a vector of coordinates.
std::vector<Coordinates> *Shape::getShape() { // return coordinates;
  if (!coordsUpToDate) {
    *coordinates = coordmap_->getCoordinates();
    coordsUpToDate = true;
  }
  return coordinates;
}

/// Get the shape as a vector of coordinates, where the parameter will be filled
/// with these coordinates
/// @param coords Reference to a pointer of coordinates, which will hold the
/// coordinates of the shape
void Shape::getShape(std::vector<Coordinates> &coords) {
  if (!coordsUpToDate) {
    *coordinates = coordmap_->getCoordinates();
    coordsUpToDate = true;
  }
  coords = *coordinates;
}

/// @brief Get the shape as a CoordinateMap
CoordinateMap *Shape::getMap() {
  if (!coordsUpToDate) {
    *coordinates = coordmap_->getCoordinates();
    coordsUpToDate = true;
  }
  return coordmap_;
}

/// Get the minimum X value in the vector of coordinates
const int Shape::getMinX() const {
  return coordmap_->getMinX();
  /*
  // If no coordinates, return -1 to indicate an error
  if (!(coordinates->size() > 0)) {
    return -1;
  }
  // If this function ran before, minX_ member will have been set, which means
  // repeating the expensive for loop is not needed and the value can be
  // returned immediately
  if (minX_ != -1)
    return minX_;

  // Initialise the first element
  int minX = coordinates->at(0).getX();

  // Loop over the elements to determine the minimum value
  for (auto &el : *coordinates) {
    if (el.getX() < minX) {
      minX = el.getX();
    }
  }

  return minX;*/
}

/// Get the maximum X value in the vector of coordinates
const int Shape::getMaxX() const {
  return coordmap_->getMaxX();
  /*
  // If no coordinates, return -1 to indicate an error
  if (!(coordinates->size() > 0)) {
    return -1;
  }
  // If this function ran before, maxX_ member will have been set, which means
  // repeating the expensive for loop is not needed and the value can be
  // returned immediately
  if (maxX_ != -1)
    return maxX_;

  // Initialise the first element
  int maxX = coordinates->at(0).getX();
  // Loop over the elements to determine the maximum value
  for (auto &el : *coordinates) {
    if (el.getX() > maxX) {
      maxX = el.getX();
    }
  }

  return maxX;*/
}

/// Get the minimum Y value in the vector of coordinates
const int Shape::getMinY() const {
  return coordmap_->getMinY();
  /*
  // If no coordinates, return -1 to indicate an error
  if (!(coordinates->size() > 0)) {
    return -1;
  }
  // If this function ran before, minY_ member will have been set, which means
  // repeating the expensive for loop is not needed and the value can be
  // returned immediately
  if (minY_ != -1)
    return minY_;

  // Initialise the first element
  int minY = coordinates->at(0).getY();

  // Loop over the elements to determine the minimum value
  for (auto &el : *coordinates) {
    if (el.getX() < minY) {
      minY = el.getX();
    }
  }

  return minY;*/
}

/// Get the maximum Y value in the vector of coordinates
const int Shape::getMaxY() const {
  return coordmap_->getMaxY();
  /*
  // If no coordinates, return -1 to indicate an error
  if (!(coordinates->size() > 0)) {
    return -1;
  }
  // If this function ran before, maxY_ member will have been set, which means
  // repeating the expensive for loop is not needed and the value can be
  // returned immediately
  if (maxY_ != -1)
    return maxY_;

  // Initialise the first element
  int maxY = coordinates->at(0).getY();
  // Loop over the elements to determine the maximum value
  for (auto &el : *coordinates) {
    if (el.getX() > maxY) {
      maxY = el.getX();
    }
  }

  return maxY;*/
}

/// Return the size of the coordinates
const int Shape::size() const { return coordinates->size(); }

bool Circle::overlaps(Shape &other) { return false; }
