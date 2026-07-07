#include <string>
#include "Dealer.h"


void Dealer::hit(Card card)
{
    hand.addCard(card);
}


Hand& Dealer::getHand()
{
    return hand;
}


void Dealer::play(Deck& deck)
{
    while(hand.getValue() < 17)     // zieht bis 17 nach normalen Regeln
    {
        hit(deck.drawCard());
    }
}

void Dealer::reset()
{
    hand.clear();
}