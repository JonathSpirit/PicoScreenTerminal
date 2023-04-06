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
    
    Position operator-(const Position& r) const;
    Position operator+(const Position& r) const;

    bool operator==(const Position& r) const;
    bool operator!=(const Position& r) const;
};

class CharBuffer
{
public:
    CharBuffer();
    explicit CharBuffer(const Size& size);
    CharBuffer(const CharBuffer& r) = default;
    CharBuffer(CharBuffer&& r) noexcept;
    ~CharBuffer() = default;

    CharBuffer& operator= (const CharBuffer& r) = default;
    CharBuffer& operator= (CharBuffer&& r) noexcept;
    
    void create(Size size, char defaultValue=' ');
    void clear(char value=' ');

    const Size& getSize() const;

    void set(Position pos, char value);
    void setString(Position pos, const char* value);
    void setString(Position pos, const std::string& value);
    void setBuffer(Position pos, const CharBuffer& value);
    void setRectangle(Position pos, Size size, char fillValue=' ', unsigned int borderSize=0, char borderValue=' ');

    char get(Position pos) const;
    
private:
    Size g_size;
    std::vector<char> g_buffer;
};

#endif //_C_CHARBUFFER_HPP_INCLUDED_