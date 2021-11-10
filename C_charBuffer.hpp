#ifndef _C_CHARBUFFER_HPP_INCLUDED_
#define _C_CHARBUFFER_HPP_INCLUDED_

#include <vector>
#include <string>

struct Size
{
    std::size_t _w;
    std::size_t _h;
};

struct Position
{
    int _x;
    int _y;
    
    Position operator-(const Position& r);
    Position operator+(const Position& r);

    bool operator==(const Position& r);
    bool operator!=(const Position& r);
};

class CharBuffer
{
public:
    CharBuffer();
    CharBuffer(const Size& size);
    CharBuffer(const CharBuffer& r) = default;
    CharBuffer(CharBuffer&& r);
    ~CharBuffer() = default;

    CharBuffer& operator= (const CharBuffer& r) = default;
    CharBuffer& operator= (CharBuffer&& r);
    
    void create(const Size& size, char defaultValue=' ');
    void clear(char value=' ');

    const Size& getSize() const;

    void set(const Position& pos, char value);
    void setString(Position pos, const char* value);
    void setString(Position pos, const std::string& value);
    void setBuffer(Position pos, const CharBuffer& value);

    char get(const Position& pos) const;
    
private:
    Size g_size;
    std::vector<std::vector<char> > g_buffer;
};

#endif //_C_CHARBUFFER_HPP_INCLUDED_