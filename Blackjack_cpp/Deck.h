#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // shuffle
#include <random>     // random_device, std::default_random_engine
#include "Card.h"

class Deck
{
private:
    std::vector<Card> cards;    // Liste vom Typ Card

public:
    Deck(int numberOfDecks);
    int getCardValue(std::string rank);
    void shuffle();
    Card drawCard();
    bool empty();
};