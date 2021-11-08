#ifndef _C_SCREEN_HPP_INCLUDED_
#define _C_SCREEN_HPP_INCLUDED_

#include "C_charBuffer.hpp"

class Screen : public CharBuffer
{
public:
    Screen(const Size& size);
    ~Screen() = default;
    
    void draw();

    void setPositionOffset(const Position& offset);
    const Position& getPositionOffset() const;

private:
    Position g_offset;
};

#endif //_C_SCREEN_HPP_INCLUDED_