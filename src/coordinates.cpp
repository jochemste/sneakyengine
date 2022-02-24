#include "coordinates.hpp"

Coordinates::Coordinates(int x_, int y_, int z_): x(x_), y(y_), z(z_){
}

Coordinates::~Coordinates(){

}

int Coordinates::getX(){
  return x;
}
int Coordinates::getY(){
  return y;
}
int Coordinates::getZ(){
  return z;
}

void Coordinates::setX(int x_){
  x=x_;
}
void Coordinates::setY(int y_){
  y=y_;
}
void Coordinates::setZ(int z_){
  z=z_;
}
