#pragma once // stellt sicher das header nur einmal compeliert/übersetzt wird --> nicht notwendig aber good use 

#include <string>

class Card
{
public:
    std::string c_type;    // Kreuz,Pik,Herz,Karo
    std::string c_rank;   // Ass,2-10,B,D,K
    int value;          // Wert der Karte in Blackjack --> Ass,B,D,K

    Card(std::string s, std::string r, int v);
};