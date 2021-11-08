#ifndef _C_SCREEN_HPP_INCLUDED_
#define _C_SCREEN_HPP_INCLUDED_

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
    
    Position operator+(const Position& r);
};

class Image
{
public:
    Image() = default;
    Image(const Size& size, char defaultValue=' ');
    ~Image() = default;
    
    void create(const Size& size, char defaultValue=' ');
    
    const Size& getSize() const;
    
    void set(const Position& pos, char value);
    char get(const Position& pos) const;
    
private:
    Size g_size;
    std::vector<std::vector<char> > g_data;
};

class Screen
{
public:
    Screen(const Size& size);
    ~Screen() = default;
    
    void draw();
    void clear();
    
    void set(const Position& pos, char value);
    void setString(Position pos, const char* value);
    void setString(Position pos, const std::string& value);
    void setImage(Position pos, const Image& value);
    
private:
    Size g_size;
    std::vector<std::vector<char> > g_screen;
};

#endif //_C_SCREEN_HPP_INCLUDED_