#ifndef TEACHERSREPOSITORY_H
#define TEACHERSREPOSITORY_H
#include "userrepository.h"
#include <QMessageBox>


class TeachersRepository: public UserRepository
{   QStringList options = {"отсутствует","кандидат наук","доктор наук"};   
    QPushButton* button_cancel;      
    TestingComponents object;
    QList<QString>widget_values;
public:
    TeachersRepository();
    void create();
    bool check_empty_fields();
    QList<QString>pass_widget_values();
    QPushButton* button_ok;
    QComboBox* combo_box;
    QLineEdit* lineEdit_first_name;
    QLineEdit* lineEdit_last_name;
    QLineEdit* lineEdit_patronymic;
    QLineEdit* lineEdit_salary;
};

#endif // TEACHERSREPOSITORY_H
