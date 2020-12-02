#include <iostream>
#include "GameBoard.hpp"

using namespace std;

int main(void)
{
    GameBoard gb;
    gb.initializeGameBoard();
    gb.gamePreparation();
    //gb.gameplay();
    gb.test();
    gb.gameEnd();
}