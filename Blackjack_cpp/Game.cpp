#include <iostream>
#include "Game.h"


// Game game_4decks(4);       bsp aufruf für main 

Game::Game(int numberOfDecks)
    : deck(numberOfDecks)
    {
    this->numberOfDecks = numberOfDecks;
    bet = 10;
    }


void Game::start()
{
    placeBet();
    deck.shuffle();

    player.hit(deck.drawCard());
    player.hit(deck.drawCard());

    dealer.hit(deck.drawCard());
    dealer.hit(deck.drawCard());

    std::cout << "Spieler:\n";
    player.getHand().print();

    std::cout << "\nDealer:\n";
    dealer.getHand().print();

    playerTurn();


    if(!player.getHand().busted())
    {
        dealerTurn();
    }


    checkWinner();
}

void Game::playerTurn()
{
    char choice;

    while(true)
    {
        std::cout << "\nDeine Hand:\n";
        player.getHand().print();

        std::cout << "\nHit oder Stand? (h/s): ";
        std::cin >> choice;
        if(choice == 'h' || choice == 'H')
        {
            player.hit(deck.drawCard());

            if(player.getHand().busted())
            {
                std::cout << "\n busted\n";
                player.getHand().print();
                break;
            }
        }
        else if(choice == 's' || choice == 'S')
        {
            std::cout << "\n stand.\n";
            break;
        }
        else
        {
            std::cout << "bitte h für hit oder s für stand eingeben\n";
        }
    }
}

void Game::dealerTurn()
{
    dealer.play(deck);
}

void Game::checkWinner()
{
    int playerValue = player.getHand().getValue();
    int dealerValue = dealer.getHand().getValue();


    std::cout << "\n--- Ergebnis ---\n";

    std::cout << "Spieler: "
              << playerValue
              << std::endl;

    std::cout << "Dealer: "
              << dealerValue
              << std::endl;


    if(player.getHand().busted())
    {
        std::cout << "Spieler ist bust. Dealer gewinnt!\n";
    }

    else if(dealer.getHand().busted())
    {
        std::cout << "Dealer ist bust. Spieler gewinnt!\n";
        player.addMoney(bet * 2);
    }

    else if(playerValue > dealerValue)
    {
        std::cout << "Spieler gewinnt!\n";
        player.addMoney(bet * 2);
    }

    else if(dealerValue > playerValue)
    {
        std::cout << "Dealer gewinnt!\n";
    }

    else
    {
        std::cout << "Unentschieden!\n";        // z.B dealer und spieler haben beide 19
        player.addMoney(bet);
    }
    player.saveBalance();
}

void Game::placeBet()
{
    while(true)
    {
        std::cout << "Guthaben: $"
                  << player.getBalance()
                  << "\n";


        std::cout << "Wette (1-20$): ";

        std::cin >> bet;


        if(bet >= 1 && bet <= 20 &&
           player.removeMoney(bet))
        {
            std::cout << "Wette gesetzt: $"
                      << bet
                      << "\n";
            break;
        }

        else
        {
            std::cout << "Ungueltige Wette!\n";
        }
    }
}

void Game::reset()
{
    player.reset();
    dealer.reset();

    deck = Deck(numberOfDecks);
}