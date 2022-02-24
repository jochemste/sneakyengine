#include "colour.h"

void Colour::setRed(int r){
  red=r;
}
void Colour::setGreen(int g){
  green=g;
}

void Colour::setBlue(int b){
  blue=b;
}

void Colour::setAlpha(int a){
  alpha=a;
}

int Colour::getRed(){
  return red;
}

int Colour::getGreen(){
  return green;
}

int Colour::getBlue(){
  return blue;
}

int Colour::getAlpha(){
  return alpha;
}

Red::Red(){
  red=255;
  green=0;
  blue=0;
  alpha=255;
}

Green::Green(){
  red=255;
  green=0;
  blue=0;
  alpha=255;
}

Blue::Blue(){
  red=255;
  green=0;
  blue=0;
  alpha=255;
}
