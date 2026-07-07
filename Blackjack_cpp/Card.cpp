// #include <iostream>

#include <string>
#include "Card.h"

Card::Card(std::string f, std::string r, int v)
{
    this->c_type = f;
    this->c_rank = r;
    this->value = v;
}