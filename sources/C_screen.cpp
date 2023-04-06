#include "C_screen.hpp"
#include <iostream>

Screen::Screen(Size size) :
        CharBuffer(size),
        g_offset({0,0})
{}

void Screen::draw()
{
    for (int y=0; y<this->getSize()._h; ++y)
    {
        for (int x=0; x<this->getSize()._w; ++x)
        {
            std::cout << this->get({x+this->g_offset._x, y+this->g_offset._y});
        }
        std::cout << std::endl;
    }
    std::cout << "\e[1;1H";
}

void Screen::setPositionOffset(Position offset)
{
    this->g_offset = offset;
}
const Position& Screen::getPositionOffset() const
{
    return this->g_offset;
}