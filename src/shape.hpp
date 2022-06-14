#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "coordinates.hpp"

#include <cmath>
#include <string>
#include <vector>

// @brief Base class for shapes
class Shape {
public:
  explicit Shape(const std::string id = "none");
  explicit Shape(CoordinateMap *cm, const std::string id = "none");
  ~Shape();

  const std::string getId() { return id_; };
  void move(int x_, int y_);
  virtual bool overlaps(Shape &other);

  std::vector<Coordinates> *getShape();
  void getShape(std::vector<Coordinates> &coords);
  CoordinateMap *getMap();
  const int getMinX() const;
  const int getMaxX() const;
  const int getMinY() const;
  const int getMaxY() const;

  const int size() const;

protected:
  const std::string id_;
  std::vector<Coordinates> *coordinates;
  CoordinateMap *coordmap_;
  int minX_ = -1;
  int maxX_ = -1;
  int minY_ = -1;
  int maxY_ = -1;

private:
  bool coordsUpToDate;
};

class Circle : public Shape {
public:
  Circle() = delete;
  Circle(int center_x, int center_y, int radius, bool solid = false)
      : Shape("circle"), radius_(radius) {
    if (solid == true) {
      for (int x = center_x - radius; x <= center_x + radius; x++) {
        for (int y = center_y - radius; y <= center_y + radius; y++) {
          if ((std::pow(center_y - y, 2) + std::pow(center_x - x, 2)) <=
              std::pow(radius, 2)) {
            coordinates->push_back(Coordinates(x, y, 0));
          }
        }
      }
    } else {
      for (double t = 0; t < 2 * M_PI; t += 0.01) {
        coordinates->push_back(Coordinates((center_x + radius * std::cos(t)),
                                           (center_y + radius * std::sin(t)),
                                           0));
      }
    }
    coordmap_->setCoordinates(*coordinates);
  }

  bool overlaps(Shape &other) override;

private:
  const int radius_ = 0;
};

class Rectangle : public Shape {
public:
  Rectangle() = delete;
  Rectangle(int left_x, int top_y, int width, int height, bool solid = false)
      : Shape("rect") {
    // Define other extremes
    int right_x = left_x + width;
    int bottom_y = top_y + height;

    if (solid == true) { // Fill square
      for (int x = left_x; x <= right_x; x++) {
        for (int y = top_y; y <= bottom_y; y++) {
          coordinates->push_back(Coordinates(x, y, 0));
        }
      }

    } else { // Create lines
      // Top line and bottom line
      for (int x = left_x; x < right_x; x++) {
        coordinates->push_back(Coordinates(x, top_y, 0));
        coordinates->push_back(Coordinates(x, bottom_y, 0));
      }
      // Left line and right line
      for (int y = top_y; y < bottom_y; y++) {
        coordinates->push_back(Coordinates(left_x, y, 0));
        coordinates->push_back(Coordinates(right_x, y, 0));
      }
    }
    coordmap_->setCoordinates(*coordinates);
  }

private:
};

#endif
