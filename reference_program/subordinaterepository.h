#ifndef SUBORDINATEREPOSITORY_H
#define SUBORDINATEREPOSITORY_H
#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include "mainwindow.h"


class SubordinateRepository:public QDialog
{
    QPushButton* button_ok;
    QPushButton* button_cancel;
    QGridLayout* layout;
public:
    SubordinateRepository(QWidget* pwgt = 0);
    void create(QTableWidget*,QStringList);
    QTableWidget* table;
public slots:  

};

#endif // SUBORDINATEREPOSITORY_H
