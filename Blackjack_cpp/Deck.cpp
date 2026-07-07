#include "Deck.h"
#include <algorithm>
#include <random>

int Deck::getCardValue(std::string rank)
{
    if (rank == "Ass")  // kann 1 oder 11 sein falls später summe der karten über 21 seien sollte und ein ass dabei ist wird es automatisch auf 1 gesetzt
    {
        return 11;
    }

    if (rank == "Bube" ||
        rank == "Dame" ||
        rank == "Koenig")
    {
        return 10;
    }

    return std::stoi(rank); //stoi --> cast string to int
}


Deck::Deck(int numberOfDecks)
{
    std::vector<std::string> c_types =
    {
    "Herz","Karo","Pik","Kreuz"
    };

    std::vector<std::string> c_raenge =
    {   
    "Ass",  // 1 oder 11
    "2","3","4","5","6","7","8","9","10",
    "Bube","Dame","Koenig" //10 
    };

    for (int deck = 0; deck < numberOfDecks; deck++)
    {
        for (int i = 0; i < c_types.size(); i++)
        {
            for (int j = 0; j < c_raenge.size(); j++)
            {
                int wert = getCardValue(c_raenge[j]);
                //Card newCard = Card(c_types[i], c_raenge[j], wert);
                //cards.push_back(newCard);
                cards.push_back(Card(c_types[i], c_raenge[j], wert));

            }
        }
    } 
}

void Deck::shuffle()
{
    std::shuffle(
        cards.begin(),      //erstes Element der Datenstruktur
        cards.end(),        //letztes Element+1 der Datenstruktur
        std::default_random_engine(std::random_device{}()) // erzeugt seed
    );
}

Card Deck::drawCard()
{
    Card card = cards.back();
    cards.pop_back();      // nimm die letzte Karte aus dem Deck
    return card;
}