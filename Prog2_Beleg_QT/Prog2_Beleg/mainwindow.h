/*
Name:Andreas Gröber
Matr.Nr.:47708
Studiengruppe:19/041/01
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "add_item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_bt_view_item_clicked();
void on_bt_add_item_clicked();

void on_bt_view_person_clicked();
void on_bt_add_person_clicked();

void on_bt_search_item_clicked();
void on_bt_search_person_clicked();

void on_bt_delete_item_clicked();
void on_bt_delete_person_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
