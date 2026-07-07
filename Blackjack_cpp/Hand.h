#pragma once

#include <vector>
#include "Card.h"

class Hand
{
private:
    std::vector<Card> cards;

public:
    void addCard(Card card);

    int getValue();

    bool busted();

    void print();

    void clear();
};