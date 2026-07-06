/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef ADD_PERSON_H
#define ADD_PERSON_H

#include <QDialog>

namespace Ui {
class add_person;
}

class add_person : public QDialog
{
    Q_OBJECT

public:
    explicit add_person(QWidget *parent = nullptr);
    ~add_person();
    void show(); //?????

private slots:

    void on_bt_add_clicked();

private:
    Ui::add_person *ui;
    void resetElements();
};

#endif // ADD_PERSON_H
