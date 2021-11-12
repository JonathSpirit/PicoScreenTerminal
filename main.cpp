#include <iostream>
#include <vector>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "C_screen.hpp"

int getRandomInt(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int main()
{
    srand( get_absolute_time()._private_us_since_boot );

    Position snakeDirection = {1,0};
    std::vector<Position> snake;
    snake.reserve(30);
    snake.push_back({3,3});
    
    CharBuffer arena({20,20});
    for (int y=0; y<20; ++y)
    {
        for (int x=0; x<20; ++x)
        {
            if (y==0 || x==0 || y==19 || x==19)
            {
                arena.set({x,y}, '*');
            }
        }
    }
    
    Screen screen({20,20});

    Position bonus = {getRandomInt(3, screen.getSize()._w-3), getRandomInt(3, screen.getSize()._h-3)};
    
    stdio_init_all();
    while (true)
    {
        char read = ' ';
        read = getchar_timeout_us(0);

        //Change snake direction
        switch (read)
        {
        case 'w':
            snakeDirection = {0,-1};
            break;
        case 'a':
            snakeDirection = {-1,0};
            break;
        case 's':
            snakeDirection = {0,1};
            break;
        case 'd':
            snakeDirection = {1,0};
            break;
        default:
            break;
        }

        //Get new snake position
        Position snakeNewPos = snake.front() + snakeDirection;

        if (snakeNewPos._x <= 0)
        {
            snakeNewPos._x = screen.getSize()._w-2;
        }
        if (snakeNewPos._y <= 0)
        {
            snakeNewPos._y = screen.getSize()._h-2;
        }
        if (snakeNewPos._x >= screen.getSize()._w-1)
        {
            snakeNewPos._x = 1;
        }
        if (snakeNewPos._y >= screen.getSize()._h-1)
        {
            snakeNewPos._y = 1;
        }

        //Shiffting
        for (std::size_t i=snake.size()-1; i>0; --i)
        {
            snake[i] = snake[i-1];
        }

        //Apply new pos
        snake.front() = snakeNewPos;

        //Check for game over
        for (std::size_t i=1; i<snake.size(); ++i)
        {
            if (snake.front() == snake[i])
            {
                return 0;
            }
        }

        //Check bonus
        if (snake.front() == bonus)
        {
            snake.push_back(snake.back());
            bonus = {getRandomInt(3, screen.getSize()._w-3), getRandomInt(3, screen.getSize()._h-3)};
        }

        screen.clear();

        //Draw arena
        screen.setBuffer({0,0}, arena);

        //Draw snake
        for (std::size_t i=0; i<snake.size(); ++i)
        {
            screen.set(snake[i], '+');
        }

        //Draw bonus
        screen.set(bonus, '&');

        //Draw

        screen.setString({3,0}, "The snake");
        
        screen.draw();
        
        sleep_ms(300);
    }
    return 0;
}
