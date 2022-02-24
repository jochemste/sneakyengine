#ifndef COORDINATES_HPP
#define COORDINATES_HPP

class Coordinates{
 public:
  Coordinates(int, int, int);
  ~Coordinates();

  int getX();
  int getY();
  int getZ();
  
  void setX(int x_);
  void setY(int y_);
  void setZ(int z_);

 private:
  int x;
  int y;
  int z;
};

#endif
