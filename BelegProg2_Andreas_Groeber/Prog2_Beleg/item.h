/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef ITEM_H
#define ITEM_H

#include <QString>

class item
{
public:
    item();
    virtual ~item()=default;
    void putdata();

    QString Name;
    QString Autor;
    QString Art;
    QString Anzahl;
    QString Verfuegbar;
};

#endif // ITEM_H
