#include "userrepository.h"


UserRepository::UserRepository(QWidget* pointer_widget): QDialog(pointer_widget, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  button_ok = new QPushButton("Добавить");
  button_cancel = new QPushButton("Отменить");
  connect(button_ok,&QPushButton::clicked,this,&UserRepository::check_empty_fields);
  connect(button_cancel,&QPushButton::clicked,this,&UserRepository::reject);
}

void UserRepository::create()
{   
    paint = QPalette();
    color_blue.setRgb(0,255,255);
    paint.setColor(QPalette::Background,color_blue);
    this->setPalette(paint);
    this->setWindowTitle("Добавить студента");
    lineEdit_first_name = new QLineEdit;
    lineEdit_last_name = new QLineEdit;
    lineEdit_patronymic = new QLineEdit;
    lineEdit_first_name->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
    lineEdit_last_name->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
    lineEdit_patronymic->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
    label_first_name = new QLabel("Фамилия");
    label_last_name  = new QLabel("Имя");
    label_patronymic = new QLabel("Отчество");
    label_birthday = new QLabel("Дата рождения");
    label_grant = new QLabel("Получает стипендию");
    combo_box = new QComboBox();
    combo_box->addItems(options);
    date_edit = new QDateEdit();
    date.toString("dd.MM.yyyy");
    date_edit->setDate(date);
    label_first_name->setBuddy(lineEdit_first_name);
    label_last_name->setBuddy(lineEdit_last_name);
    label_patronymic->setBuddy(lineEdit_patronymic);
    grid_layout = new QGridLayout;
    grid_layout->addWidget(label_first_name,0,0);
    grid_layout->addWidget(label_last_name,1,0);
    grid_layout->addWidget(label_patronymic,2,0);
    grid_layout->addWidget(lineEdit_first_name,0,1);
    grid_layout->addWidget(lineEdit_last_name,1,1);
    grid_layout->addWidget(lineEdit_patronymic,2,1);
    grid_layout->addWidget(label_birthday,3,0);
    grid_layout->addWidget(date_edit,3,1);
    grid_layout->addWidget(label_grant,4,0);
    grid_layout->addWidget(combo_box,4,1);
    grid_layout->addWidget(button_ok,5,0);
    grid_layout->addWidget(button_cancel,5,1);
    setLayout(grid_layout);
}

bool UserRepository::check_empty_fields()
{    
    if(lineEdit_first_name->text().size()!=0 && lineEdit_last_name->text().size()!=0 &&
       lineEdit_patronymic->text().size()!=0)
      {this->accept();return true;}
    else
    {
      QMessageBox::warning(0,"Ошибка","Заполните пустые поля!");
      object.check_empty_fields("Не заполнено одно из полей");return false;
    }
}

QString UserRepository::change_input_case(QString str)
{
    QString word_a = str[0].toUpper(); QString word_b;
    for(int i=1; i < str.size();++i){word_b+=str[i].toLower();}
       return word_a+word_b;
}

QList<QString>UserRepository::pass_widget_values()
{
    QDate date = date_edit->date();
    widget_values.push_back(change_input_case(lineEdit_first_name->text()));
    widget_values.push_back(change_input_case(lineEdit_last_name->text()));
    widget_values.push_back(change_input_case(lineEdit_patronymic->text()));   
    widget_values.push_back(change_input_case(date.toString("dd.MM.yyyy")));
    widget_values.push_back(change_input_case(combo_box->currentText()));
    object.pass_widget_values(widget_values.size());
    return widget_values;
}
