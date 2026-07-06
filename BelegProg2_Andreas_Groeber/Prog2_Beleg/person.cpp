/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#include "person.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
person::person()
{

}

void person::putdata()
{
    QFile PFile("Personlisttest.csv");
    if(PFile.open(QFile::Append|QFile::Text))
    {
        QTextStream stream(&PFile);
        stream << this->    person_name + "," +
                  this->    medien_name + "," +
                  this->    medien_art +  "," +
                  this->    adress + "," +
                  this->    date + "," +
                  '\n';

        PFile.flush();
        PFile.close();
    }
    else
    {
        QMessageBox ErrorMsg;
        ErrorMsg.setText("schreiben in personlist nicht möglich");
        ErrorMsg.exec();
    }
}
