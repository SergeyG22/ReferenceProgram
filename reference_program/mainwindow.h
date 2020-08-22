#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <QProcess>
#include "userrepository.h"
#include "teachersrepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void create_user();
    void read_user();
    void remove_user();
    void value_selected_row();
    void function_redrawing_subordinate_table();
private:
    Ui::MainWindow *ui;
    QStringList upper_headers_top {"Фамилия","Имя","Отчество","Дата рождения","Получает стипендию"};
    QStringList upper_headers_low {"Фамилия","Имя","Отчество","Зарплата","Ученая степень"};
    QMultiMap<int,QList<QString>>map_sub;
    int row =-1;
};
#endif // MAINWINDOW_H
