#include "teachersrepository.h"

TeachersRepository::TeachersRepository() {  }


void TeachersRepository::create()
{
  this->setWindowTitle("Добавить преподователя");
  QColor color;
  color.setRgb(0,255,255);
  QPalette paint = QPalette();
  paint.setColor(QPalette::Background,color);
  this->setPalette(paint);
  QLabel* label_first_name = new QLabel("Фамилия");
  QLabel* label_last_name  = new QLabel("Имя");
  QLabel* label_patronymic = new QLabel("Отчество");
  QLabel* label_salary = new QLabel("Зарплата(руб.)");
  QLabel* label_grant = new QLabel("Ученая степень");
  button_ok = new QPushButton("Добавить");
  button_cancel = new QPushButton("Отменить");
  lineEdit_first_name = new QLineEdit;
  lineEdit_last_name = new QLineEdit;
  lineEdit_patronymic = new QLineEdit;
  lineEdit_salary = new QLineEdit;
  lineEdit_first_name->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
  lineEdit_last_name->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
  lineEdit_patronymic->setValidator(new QRegExpValidator( QRegExp( "[A-Za-zА-Яа-я]{1,16}")));
  lineEdit_salary->setValidator(new QRegExpValidator( QRegExp( "[0-9]{1,16}")));
  combo_box = new QComboBox;
  combo_box->addItems(options);
  QGridLayout* layout = new QGridLayout;
  layout->addWidget(label_first_name,0,0);
  layout->addWidget(lineEdit_first_name,0,1);
  layout->addWidget(label_last_name,1,0);
  layout->addWidget(lineEdit_last_name,1,1);
  layout->addWidget(label_patronymic,2,0);
  layout->addWidget(lineEdit_patronymic,2,1);
  layout->addWidget(label_salary,3,0);
  layout->addWidget(lineEdit_salary,3,1);
  layout->addWidget(label_grant,4,0);
  layout->addWidget(combo_box,4,1);
  layout->addWidget(button_ok,5,0);
  layout->addWidget(button_cancel,5,1);
  setLayout(layout);
  connect(button_ok,&QPushButton::clicked,this,&TeachersRepository::check_empty_fields);
  connect(button_cancel,&QPushButton::clicked,this,&TeachersRepository::reject);
}

bool TeachersRepository::check_empty_fields()
{
    if(lineEdit_first_name->text().size()!=0 && lineEdit_last_name->text().size()!=0 &&
       lineEdit_patronymic->text().size()!=0 && lineEdit_salary->text().size()!=0)
    { this->accept();return true; }
    else
    {
      QMessageBox::warning(0,"Ошибка","Заполните пустые поля!");
      object.check_empty_fields("Не заполнено одно из полей");return false;
    }
}


QList<QString>TeachersRepository::pass_widget_values()
{
    widget_values.push_back(change_input_case(this->lineEdit_first_name->text()));
    widget_values.push_back(change_input_case(this->lineEdit_last_name->text()));
    widget_values.push_back(change_input_case(this->lineEdit_patronymic->text()));
    widget_values.push_back(change_input_case(this->lineEdit_salary->text()));
    widget_values.push_back(this->combo_box->currentText());
    object.pass_widget_values(widget_values.size());
    return widget_values;
}
