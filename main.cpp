#include <iostream>
#include <vector>
#include "pico/stdlib.h"
#include "C_screen.hpp"

int main()
{
    unsigned char i=0;
    
    CharBuffer testBuffer({2,2});
    testBuffer.set({0,0}, 219);//201
    testBuffer.set({1,0}, 219);//187
    testBuffer.set({0,1}, 219);//200
    testBuffer.set({1,1}, 219);//188
    
    Screen screen({20,20});
    
    stdio_init_all();
    while (true)
    {
        char read = ' ';
        read = getchar_timeout_us(0);
        
        screen.set({2,0}, read);
        screen.set({0,0}, i+'0');
        screen.setString({3,2}, "Bonjour UwU");
        screen.setBuffer({5,5}, testBuffer);
        
        if (++i > 9)
        {
            i=0;
        }
        
        screen.draw();
        
        sleep_ms(1000);
    }
    return 0;
}
