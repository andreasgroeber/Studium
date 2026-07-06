/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef PERSON_H
#define PERSON_H

#include <QString>

class person
{
public:
    person();
    ~person()=default;
    void putdata();

    QString person_name;
    QString medien_name;
    QString medien_art;
    QString adress;
    QString date;           //Rückgabedatum
};

#endif // PERSON_H
