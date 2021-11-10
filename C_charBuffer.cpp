#include "C_charBuffer.hpp"

///Position

Position Position::operator-(const Position& r)
{
    return {this->_x - r._x, this->_y - r._y};
}
Position Position::operator+(const Position& r)
{
    return {this->_x + r._x, this->_y + r._y};
}

bool Position::operator==(const Position& r)
{
    return this->_x==r._x && this->_y == r._y;
}
bool Position::operator!=(const Position& r)
{
    return this->_x!=r._x || this->_y != r._y;
}

///CharBuffer

CharBuffer::CharBuffer() :
        g_size({1,1})
{
    this->create(this->g_size);
}
CharBuffer::CharBuffer(const Size& size) :
        g_size(size)
{
    this->create(size);
}
CharBuffer::CharBuffer(CharBuffer&& r) :
    g_size(r.g_size),
    g_buffer(std::move(r.g_buffer))
{
    r.create({1,1});
}

CharBuffer& CharBuffer::operator= (CharBuffer&& r)
{
    this->g_size = r.g_size;
    this->g_buffer = std::move(r.g_buffer);
    r.create({1,1});
    return *this;
}

void CharBuffer::create(const Size& size, char defaultValue)
{
    this->g_size = size;
    this->g_buffer.resize(size._h);
    for (std::size_t i=0; i<size._h; ++i)
    {
        this->g_buffer[i].resize(size._w, defaultValue);
    }
}
void CharBuffer::clear(char value)
{
    for (std::size_t y=0; y<this->g_size._h; ++y)
    {
        for (std::size_t x=0; x<this->g_size._w; ++x)
        {
            this->g_buffer[y][x] = value;
        }
    }
}

const Size& CharBuffer::getSize() const
{
    return this->g_size;
}

void CharBuffer::set(const Position& pos, char value)
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        this->g_buffer[pos._y][pos._x] = value;
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
    for (std::size_t i=0; i<value.size(); ++i)
    {
        this->set(pos, value[i]);
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

char CharBuffer::get(const Position& pos) const
{
    if (pos._x>=0 && pos._x<this->g_size._w && pos._y>=0 && pos._y<this->g_size._h)
    {
        return this->g_buffer[pos._y][pos._x];
    }
    return 0;
}
