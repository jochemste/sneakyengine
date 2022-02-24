#include "shape.hpp"

#include <iostream>

Shape::Shape(){
  coordinates = new std::vector<Coordinates>;
}

Shape::~Shape(){
  delete coordinates;
}

void Shape::move(int x_, int y_){
  for(auto& el: *coordinates){
    el.setX(el.getX()+x_);
    el.setY(el.getY()+y_);
  }
}

std::vector<Coordinates>* Shape::getShape(){
  return coordinates;
}

void Shape::getShape(std::vector<Coordinates>*& coords){
  coords = coordinates;
}
