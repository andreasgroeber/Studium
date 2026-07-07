#pragma once

#include "Hand.h"
#include "Deck.h"

class Dealer
{
private:
    Hand hand;

public:
    void hit(Card card);
    Hand& getHand();
    void play(Deck& deck);

    void reset();
};