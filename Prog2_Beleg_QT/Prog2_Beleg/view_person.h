/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef VIEW_PERSON_H
#define VIEW_PERSON_H

#include <QDialog>

namespace Ui {
class view_person;
}

class view_person : public QDialog
{
    Q_OBJECT

public:
    explicit view_person(QWidget *parent = nullptr);
    ~view_person();

private slots:
    void on_bt_nsort_clicked();

    void on_bt_nsort2_clicked();

private:
    Ui::view_person *ui;
};

#endif // VIEW_PERSON_H
