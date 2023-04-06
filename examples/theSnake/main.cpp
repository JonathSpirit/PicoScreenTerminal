#include <iostream>
#include <vector>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/watchdog.h"
#include "C_screen.hpp"

int getRandomInt(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int main()
{
    srand( to_us_since_boot(get_absolute_time()) );

    Position snakeDirection = {1,0};
    std::vector<Position> snake;
    snake.reserve(30);
    snake.push_back({3,3});
    int nbBonusCollected = 0;
    
    CharBuffer arena({20,20});
    arena.setRectangle({0,0}, {20,20}, ' ', 1, '*');

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
            if (snakeDirection != (Position){0,1})
            {
                snakeDirection = (Position){0,-1};
            }
            break;
        case 'a':
            if (snakeDirection != (Position){1,0})
            {
                snakeDirection = {-1,0};
            }
            break;
        case 's':
            if (snakeDirection != (Position){0,-1})
            {
                snakeDirection = {0,1};
            }
            break;
        case 'd':
            if (snakeDirection != (Position){-1,0})
            {
                snakeDirection = {1,0};
            }
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
                screen.setString({0, 19}, "Score: GAME OVER");
                screen.draw();
                sleep_ms(2000);
                
                //RESET
                watchdog_reboot(0, SRAM_END, 10);
            }
        }

        //Check bonus
        if (snake.front() == bonus)
        {
            snake.push_back(snake.back());
            bonus = {getRandomInt(3, screen.getSize()._w-3), getRandomInt(3, screen.getSize()._h-3)};
            nbBonusCollected++;
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

        screen.setString({0,19}, "Score: " + std::to_string(nbBonusCollected)+" ");
        //Draw

        screen.setString({3,0}, "The snake");
        
        screen.draw();
        
        sleep_ms(300);
    }
    return 0;
}
