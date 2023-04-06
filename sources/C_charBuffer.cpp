#include "C_charBuffer.hpp"

///Position

Position Position::operator-(const Position& r) const
{
    return {this->_x - r._x, this->_y - r._y};
}
Position Position::operator+(const Position& r) const
{
    return {this->_x + r._x, this->_y + r._y};
}

bool Position::operator==(const Position& r) const
{
    return this->_x==r._x && this->_y == r._y;
}
bool Position::operator!=(const Position& r) const
{
    return this->_x!=r._x || this->_y != r._y;
}

///CharBuffer

CharBuffer::CharBuffer() :
        g_size({0,0})
{}
CharBuffer::CharBuffer(const Size& size) :
        g_size(size)
{
    this->create(size);
}
CharBuffer::CharBuffer(CharBuffer&& r) noexcept :
    g_size(r.g_size),
    g_buffer(std::move(r.g_buffer))
{
    r.g_size = {0,0};
}

CharBuffer& CharBuffer::operator= (CharBuffer&& r) noexcept
{
    this->g_size = r.g_size;
    this->g_buffer = std::move(r.g_buffer);
    r.g_size = {0,0};
    return *this;
}

void CharBuffer::create(Size size, char defaultValue)
{
    this->g_size = size;
    if (size._w == 0 || size._h == 0)
    {
        this->g_size = {0,0};
    }

    this->g_buffer.clear();
    this->g_buffer.resize(size._w * size._h, defaultValue);
}
void CharBuffer::clear(char value)
{
    for (char& c : this->g_buffer)
    {
        c = value;
    }
}

const Size& CharBuffer::getSize() const
{
    return this->g_size;
}

void CharBuffer::set(Position pos, char value)
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        this->g_buffer[pos._x + pos._y*this->g_size._w] = value;
    }
}
void CharBuffer::setString(Position pos, const char* value)
{
    std::size_t i = 0;
    while (value[i] != '\0')
    {
        this->set(pos, value[i++]);
        ++pos._x;
    }
}
void CharBuffer::setString(Position pos, const std::string& value)
{
    for (char c : value)
    {
        this->set(pos, c);
        ++pos._x;
    }
}
void CharBuffer::setBuffer(Position pos, const CharBuffer& value)
{
    for (int y=0; y<value.getSize()._h; ++y)
    {
        for (int x=0; x<value.getSize()._w; ++x)
        {
            this->set(pos + Position{x,y}, value.get({x,y}));
        }
    }
}

void CharBuffer::setRectangle(Position pos, Size size, char fillValue, unsigned int borderSize, char borderValue)
{
    for (int y=0; y<size._h; ++y)
    {
        for (int x=0; x<size._w; ++x)
        {
            if (x<borderSize || x>=size._w-borderSize || y<borderSize || y>=size._h-borderSize)
            {
                this->set(pos + Position{x,y}, borderValue);
            }
            else
            {
                this->set(pos + Position{x,y}, fillValue);
            }
        }
    }
}

char CharBuffer::get(Position pos) const
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        return this->g_buffer[pos._x + pos._y*this->g_size._w];
    }
    return '\0';
}
