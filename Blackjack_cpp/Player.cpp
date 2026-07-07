#include <stdio.h>
#include <fstream>
#include "Player.h"
#include <iostream>

Player::Player()
{
    loadBalance();
}

int Player::getBalance()
{
    return balance;
}

void Player::addMoney(int amount)
{
    balance += amount;
}

bool Player::removeMoney(int amount)
{
    if(amount > balance)
    {
        return false;
    }

    balance -= amount;
    return true;
}

void Player::hit(Card card)
{
    hand.addCard(card);
}

Hand& Player::getHand()
{
    return hand;
}

void Player::reset()
{
    hand.clear();
}

void Player::loadBalance()
{
    std::ifstream file("balance.txt");

    if(file)
    {
        file >> balance;

        std::cout << "Balance geladen: $"
                  << balance
                  << "\n";
    }
    else
    {
        balance = 100;

        std::cout << "Neue Balance erstellt: $100\n";       //default mit 100 initialisiert

        saveBalance();
    }
}

void Player::saveBalance()
{
    std::ofstream file("balance.txt");

    file << balance;
}