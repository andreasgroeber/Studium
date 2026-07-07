#pragma once

#include "Hand.h"

class Player
{
private:
    Hand hand;
    int balance;

public:
    Player();
    void hit(Card card);
    Hand& getHand();            //Hand& ist eine Referenz --> greift auf die "echten" Objekte zu nicht auf kopien davon
    int getBalance();
    void addMoney(int amount);
    bool removeMoney(int amount);   // checkt ob spieler überhaupt genug geld hat, bevor es abzieht
    void reset();

     void saveBalance();           // für dateiarbeit
     void loadBalance();
};