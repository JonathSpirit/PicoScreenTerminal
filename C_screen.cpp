#include "C_screen.hpp"
#include <iostream>

///Position

Position Position::operator+(const Position& r)
{
    return {this->_x + r._x, this->_y + r._y};
}

///Image

Image::Image(const Size& size, char defaultValue) :
    g_size(size)
{
    this->g_data.resize(size._h);
    for (std::size_t i=0; i<size._h; ++i)
    {
        this->g_data[i].resize(size._w, defaultValue);
    }
}

void Image::create(const Size& size, char defaultValue)
{
    this->g_size = size;
    this->g_data.resize(size._h);
    for (std::size_t i=0; i<size._h; ++i)
    {
        this->g_data[i].resize(size._w, defaultValue);
    }
}

const Size& Image::getSize() const
{
    return this->g_size;
}

void Image::set(const Position& pos, char value)
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        this->g_data[pos._y][pos._x] = value;
    }
}
char Image::get(const Position& pos) const
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        return this->g_data[pos._y][pos._x];
    }
    return 0;
}

///Screen

Screen::Screen(const Size& size) :
        g_size(size)
{
    this->g_screen.resize(size._h);
    for (std::size_t i=0; i<size._h; ++i)
    {
        this->g_screen[i].resize(size._w, ' ');
    }
}

void Screen::draw()
{
    for (std::size_t y=0; y<this->g_size._h; ++y)
    {
        for (std::size_t x=0; x<this->g_size._w; ++x)
        {
            std::cout << this->g_screen[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << "\e[1;1H";
}
void Screen::clear()
{
    for (std::size_t y=0; y<this->g_size._h; ++y)
    {
        for (std::size_t x=0; x<this->g_size._w; ++x)
        {
            this->g_screen[y][x] = ' ';
        }
    }
}

void Screen::set(const Position& pos, char value)
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        this->g_screen[pos._y][pos._x] = value;
    }
}
void Screen::setString(Position pos, const char* value)
{
    std::size_t i = 0;
    while (value[i] != '\0')
    {
        this->set(pos, value[i++]);
        ++pos._x;
    }
}
void Screen::setString(Position pos, const std::string& value)
{
    for (std::size_t i=0; i<value.size(); ++i)
    {
        this->set(pos, value[i]);
        ++pos._x;
    }
}
void Screen::setImage(Position pos, const Image& value)
{
    for (int y=0; y<value.getSize()._h; ++y)
    {
        for (int x=0; x<value.getSize()._w; ++x)
        {
            this->set(pos + Position{x,y}, value.get({x,y}));
        }
    }
}
