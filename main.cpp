#include <iostream>
#include <vector>
#include "pico/stdlib.h"
#include "C_screen.hpp"

int main()
{
    unsigned char i=0;
    
    Image testImage({2,2});
    testImage.set({0,0}, 219);//201
    testImage.set({1,0}, 219);//187
    testImage.set({0,1}, 219);//200
    testImage.set({1,1}, 219);//188
    
    Screen screen({20,20});
    
    stdio_init_all();
    while (true)
    {
        screen.set({0,0}, i+'0');
        screen.setString({3,2}, "Bonjour UwU");
        screen.setImage({5,5}, testImage);
        
        if (++i > 9)
        {
            i=0;
        }
        
        screen.draw();
        
        sleep_ms(1000);
    }
    return 0;
}
