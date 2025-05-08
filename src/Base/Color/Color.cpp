#include "Color.h"

Color::Color(double red, double green, double blue, double alpha){
    this->red = (float)red;
    this->green = (float)green;
    this->blue = (float)blue;
    this->alpha = (float)alpha;
}
Color::Color(double red, double green, double blue) : Color(red, green, blue, 1){}
Color::~Color(){}