#include <string>
#include <iostream>
#include "Hand.h"


void Hand::addCard(Card card)
{
 cards.push_back(card);
}

int Hand::getValue()
{
    int h_value= 0;      // Handwert später evtl anpassen bei split
    int aces=0;          //wichtig für die 1 & 11 Wertigkeit

    for(const Card& c : cards)  //const Card& schaut direkt auf das Objekt card c würde eine Kopie erstellen, es funktioniert beides
    {
        h_value += c.value;

         if(c.c_rank == "Ass")
        {
            aces++;
        }
    }
    while(h_value > 21 && aces > 0) 
    {   
        h_value -= 10;  // Mache aus Ass eine 1 entferne das Ass 
        aces--;
    }
    
    return h_value;
}

bool Hand::busted()
{
    //if(getValue()>21)
    //    {
    //    return true;
    //    }
    //    return false;     geht besser

    {
    return getValue() > 21;
    }

}

void Hand::print()
{
    for(const Card& c : cards)
    {
        std::cout << c.c_type << " "        //erst alle Karten dann den Wert
                  << c.c_rank
                  << std::endl;
    }

    std::cout << "Wert: "
              << getValue()
              << std::endl;
}

void Hand::clear()
{
    cards.clear();
}