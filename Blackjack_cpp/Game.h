#pragma once

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

class Game
{
private:
    Deck deck;
    Player player;
    Dealer dealer;

    int bet=10;      
    int numberOfDecks;

public:
    Game(int numberOfDecks);

    void start();
    void playerTurn();
    void dealerTurn();
    void checkWinner();

    void placeBet();
    void reset();
};