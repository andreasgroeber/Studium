/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef DELETE_PERSON_H
#define DELETE_PERSON_H

#include <QDialog>

namespace Ui {
class delete_person;
}

class delete_person : public QDialog
{
    Q_OBJECT

public:
    explicit delete_person(QWidget *parent = nullptr);
    ~delete_person();
    void resetElements();

private slots:
    void on_loeschen_clicked();

private:
    Ui::delete_person *ui;
};

#endif // DELETE_PERSON_H
