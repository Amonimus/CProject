#pragma once

class Color{
    public:
        Color(double red, double green, double blue, double alpha);
        Color(double red, double green, double blue);
        ~Color();
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 0;
        private:
};