#ifndef COLOUR_H
#define COLOUR_H

class Colour{

 public:

  void setRed(int r);
  void setGreen(int g);
  void setBlue(int b);
  void setAlpha(int a);
  
  int getRed();
  int getGreen();
  int getBlue();
  int getAlpha();
  
 protected:
  int red=0;
  int green=0;
  int blue=0;
  int alpha=0;
};

class Red: protected Colour{
 public:
  Red();
  
 private:
  
};

class Green: protected Colour{
 public:
  Green();
  
 private:
  
};

class Blue: protected Colour{
 public:
  Blue();
  
 private:
  
};

#endif
