#include <iostream>
#include "Game.h"

int main()
{
    Game game(4);

    char again;

    do                              //do while https://www.w3schools.com/cpp/cpp_do_while_loop.asp
    {
        game.reset();
        game.start();

        std::cout << "\nNoch eine Runde? (j/n): ";
        std::cin >> again;

    } while(again == 'j');


    return 0;
}