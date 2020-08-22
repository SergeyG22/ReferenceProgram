#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include "testingcomponents.h"


class UserRepository: public QDialog
{
    QPalette paint;
    QColor color_blue;           
    QStringList options = {"да","нет"};
    QDate date;    
    QPushButton* button_cancel;    
    QList<QString>widget_values;
    TestingComponents object;   
    QLabel* label_first_name;
    QLabel* label_last_name;
    QLabel* label_patronymic;
    QGridLayout* grid_layout;
    QLabel* label_birthday;
    QLabel* label_grant;
public:
    UserRepository(QWidget* pwgt = 0);
    QPushButton* button_ok;
    QDateEdit* date_edit;
    QComboBox* combo_box;
    QLineEdit* lineEdit_first_name;
    QLineEdit* lineEdit_last_name;
    QLineEdit* lineEdit_patronymic;
    QList<QString>pass_widget_values();
    QString change_input_case(QString);
    bool check_empty_fields();    
    void create();
public slots:

};

#endif // USERREPOSITORY_H
