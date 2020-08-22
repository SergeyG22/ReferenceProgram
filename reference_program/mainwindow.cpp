#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subordinaterepository.h"



//Important Note:

//#######################################################
//#                                                     #
//#  Teacher table row numbers are stored in QMultimap. #
//#  This QMultimap stores a QList data structure which #
//#  in turn contains row numbers and five columns      #
//#  of subordinate table values.                       #
//#                                                     #
//#######################################################################################################################
//#                                                                                                                     #
//#  map_sub.values(ui->table_widget_teachers->currentRow())[i].value(j):                                               #
//#  Where is:                                                                                                          #
//#  1) values(ui->table_widget_teachers->currentRow()) <------ teacher table row number                                #
//#  2) [i]                                             <------ subordinate table row number                            #
//#  3) value(j)                                        <------ subordinate table column number (returns string value)  #
//#                                                                                                                     #
//#######################################################################################################################





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(auto i=0;i<=4;++i)
    {
         ui->table_widget_students->setHorizontalHeaderItem(i,new QTableWidgetItem(upper_headers_top[i]));
         ui->table_widget_subordinate->setHorizontalHeaderItem(i,new QTableWidgetItem(upper_headers_top[i]));
         ui->table_widget_teachers->setHorizontalHeaderItem(i,new QTableWidgetItem(upper_headers_low[i]));
    }    
    connect(ui->pushbutton_add_student,&QPushButton::clicked,this,&MainWindow::create_user);
    connect(ui->pushbutton_add_teacher,&QPushButton::clicked,this,&MainWindow::create_user);
    connect(ui->pushbutton_add_student_in_subordinate,&QPushButton::clicked,this,&MainWindow::create_user);
    connect(ui->pushbutton_remove_student,&QPushButton::clicked,this,&MainWindow::remove_user);
    connect(ui->pushbutton_remove_teacher,&QPushButton::clicked,this,&MainWindow::remove_user);
    connect(ui->pushbutton_remove_student_from_subordinate,&QPushButton::clicked,this,&MainWindow::remove_user);
    connect(ui->pushbutton_change_student,&QPushButton::clicked,this,&MainWindow::read_user);
    connect(ui->pushbutton_change_teacher,&QPushButton::clicked,this,&MainWindow::read_user);
    connect(ui->table_widget_students,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(value_selected_row()));
    connect(ui->table_widget_teachers,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(value_selected_row()));
    connect(ui->table_widget_teachers,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(function_redrawing_subordinate_table()));
    connect(ui->table_widget_subordinate,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(value_selected_row()));
}

void MainWindow::create_user()
{   
   if(sender()->objectName()=="pushbutton_add_student")
   {
    UserRepository* open_dialogue = new UserRepository;
    open_dialogue->create();
    if (open_dialogue->exec() == UserRepository::Accepted && open_dialogue->check_empty_fields())
    {  int cell_number=0;
       ui->table_widget_students->insertRow(ui->table_widget_students->rowCount());
       for(auto i:open_dialogue->pass_widget_values())
       {
          QTableWidgetItem* item = new QTableWidgetItem(i);
          ui->table_widget_students->setItem(ui->table_widget_students->rowCount()-1,cell_number,item);
          cell_number++;
       }
    }
    delete open_dialogue;
   }
   if(sender()->objectName()=="pushbutton_add_teacher")
   {
     TeachersRepository* open_dialogue = new TeachersRepository;
     open_dialogue->create();
     if(open_dialogue->exec() == TeachersRepository::Accepted)
     {
        int cell_number=0;
        ui->table_widget_teachers->insertRow(ui->table_widget_teachers->rowCount());
        for(auto i: open_dialogue->pass_widget_values())
        {
           QTableWidgetItem* item = new QTableWidgetItem(i);
           ui->table_widget_teachers->setItem(ui->table_widget_teachers->rowCount()-1,cell_number,item);
           cell_number++;
        }
     }
     delete open_dialogue;
   }
   if(sender()->objectName()=="pushbutton_add_student_in_subordinate")
   {
     SubordinateRepository* open_dialogue = new SubordinateRepository;
     QTableWidget* table_pointer = ui->table_widget_students;
     open_dialogue->create(table_pointer,upper_headers_top);
     if(ui->table_widget_students->rowCount()>0)
   {
       if(ui->table_widget_teachers->rowCount()>0)
      {
        if(ui->table_widget_teachers->currentRow()!=-1)
         {
      if(open_dialogue->exec()== SubordinateRepository::Accepted)
     {
     QList<QString>list_students;
     ui->table_widget_subordinate->insertRow(ui->table_widget_subordinate->rowCount());
     for(auto i=0;i<=4;++i)
     {
       QTableWidgetItem* item = new QTableWidgetItem(ui->table_widget_students->item(open_dialogue->table->currentRow(),i)->text());
       ui->table_widget_subordinate->setItem(ui->table_widget_subordinate->rowCount()-1,i,item);
       list_students.push_front(item->text());
     }
      map_sub.insert(ui->table_widget_teachers->currentRow(),list_students);

    }
      delete open_dialogue;
    }
    else QMessageBox::warning(0,"Ошибка","Для добавления в таблицу подчиненных следует выбрать преподавателя в таблице \"Преподователи\"!");
   }    
    else QMessageBox::warning(0,"Ошибка","Добавьте преподавателей в таблицу \"Преподователи\"!");
   }
   else QMessageBox::warning(0,"Ошибка","Добавьте студентов в таблицу \"Cтуденты\"!");
 }
}
void MainWindow::remove_user()
{
   if(sender()->objectName()=="pushbutton_remove_student") {ui->table_widget_students->removeRow(row);row =-1;}
   if(sender()->objectName()=="pushbutton_remove_teacher") { ui->table_widget_teachers->removeRow(row);row =-1;
   ui->table_widget_subordinate->clearContents();
   ui->table_widget_subordinate->setRowCount(0);

     for(auto it = map_sub.begin();it!=map_sub.end();++it)
        {
         if(*(it)==map_sub.values(ui->table_widget_teachers->currentRow()+1)[0]){map_sub.erase(it);}
        }
   }

   if(sender()->objectName()=="pushbutton_remove_student_from_subordinate")
   {
       ui->table_widget_subordinate->removeRow(row);row=-1;
   }
}

void MainWindow::value_selected_row()
{
  if(sender()->objectName()=="table_widget_students"){ row = ui->table_widget_students->currentRow();}
  if(sender()->objectName()=="table_widget_teachers"){ row = ui->table_widget_teachers->currentRow();}
  if(sender()->objectName()=="table_widget_subordinate"){ row = ui->table_widget_subordinate->currentRow();}
}

void MainWindow::read_user()
{

 if(sender()->objectName()=="pushbutton_change_student")
 {
    if(ui->table_widget_students->currentRow()!=-1)
 {
  UserRepository* open_dialogue = new UserRepository;
  open_dialogue->create();
  open_dialogue->button_ok->setText("изменить");
  QDate date = date.fromString(ui->table_widget_students->item(ui->table_widget_students->currentRow(),3)->text(),"dd.MM.yyyy");
  open_dialogue->date_edit->setDate(date);

  QString first_name_cell = ui->table_widget_students->item(ui->table_widget_students->currentRow(),0)->text();
  QString last_name_cell = ui->table_widget_students->item(ui->table_widget_students->currentRow(),1)->text();
  QString patronymic_cell = ui->table_widget_students->item(ui->table_widget_students->currentRow(),2)->text();

  if(ui->table_widget_students->item(ui->table_widget_students->currentRow(),4)->text() == "нет"){ open_dialogue->combo_box->setCurrentText("нет");}
  if(ui->table_widget_students->item(ui->table_widget_students->currentRow(),4)->text() == "да"){ open_dialogue->combo_box->setCurrentText("да");}

  open_dialogue->lineEdit_first_name->setText(first_name_cell);
  open_dialogue->lineEdit_last_name->setText(last_name_cell);
  open_dialogue->lineEdit_patronymic->setText(patronymic_cell);

  if(open_dialogue->exec()==UserRepository::Accepted && open_dialogue->check_empty_fields())
  {
    QTableWidgetItem* first_name = new QTableWidgetItem(open_dialogue->lineEdit_first_name->text());
    QTableWidgetItem* last_name = new QTableWidgetItem(open_dialogue->lineEdit_last_name->text());
    QTableWidgetItem* patronymic = new QTableWidgetItem(open_dialogue->lineEdit_patronymic->text());
    QTableWidgetItem* date = new QTableWidgetItem(open_dialogue->date_edit->text());
    QTableWidgetItem* combo_box = new QTableWidgetItem(open_dialogue->combo_box->itemText(open_dialogue->combo_box->currentIndex()));
    ui->table_widget_students->setItem(ui->table_widget_students->currentRow(),0,first_name);
    ui->table_widget_students->setItem(ui->table_widget_students->currentRow(),1,last_name);
    ui->table_widget_students->setItem(ui->table_widget_students->currentRow(),2,patronymic);
    ui->table_widget_students->setItem(ui->table_widget_students->currentRow(),3,date);
    ui->table_widget_students->setItem(ui->table_widget_students->currentRow(),4,combo_box);

  }
  delete open_dialogue;
 }
}

 if(sender()->objectName()=="pushbutton_change_teacher")
{
   if(ui->table_widget_teachers->currentRow()!=-1)
 {
     TeachersRepository* open_dialogue = new TeachersRepository;
     open_dialogue->create();
     open_dialogue->button_ok->setText("Изменить");
     QString first_name_cell = ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),0)->text();
     QString last_name_cell = ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),1)->text();
     QString patronymic_cell = ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),2)->text();
     QString salary_cell = ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),3)->text();
     if(ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),4)->text() == "отсутствует"){ open_dialogue->combo_box->setCurrentText("отсутствует");}
     if(ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),4)->text() == "кандидат наук"){ open_dialogue->combo_box->setCurrentText("кандидат наук");}
     if(ui->table_widget_teachers->item(ui->table_widget_teachers->currentRow(),4)->text() == "доктор наук"){open_dialogue->combo_box->setCurrentText("доктор наук"); }

     open_dialogue->lineEdit_first_name->setText(first_name_cell);
     open_dialogue->lineEdit_last_name->setText(last_name_cell);
     open_dialogue->lineEdit_patronymic->setText(patronymic_cell);
     open_dialogue->lineEdit_salary->setText(salary_cell);
     if(open_dialogue->exec()==TeachersRepository::Accepted && open_dialogue->check_empty_fields())
     {
         QTableWidgetItem* first_name = new QTableWidgetItem(open_dialogue->lineEdit_first_name->text());
         QTableWidgetItem* last_name = new QTableWidgetItem(open_dialogue->lineEdit_last_name->text());
         QTableWidgetItem* patronymic = new QTableWidgetItem(open_dialogue->lineEdit_patronymic->text());
         QTableWidgetItem* salary = new QTableWidgetItem(open_dialogue->lineEdit_salary->text());
         QTableWidgetItem* combo_box = new QTableWidgetItem(open_dialogue->combo_box->itemText(open_dialogue->combo_box->currentIndex()));
         ui->table_widget_teachers->setItem(ui->table_widget_teachers->currentRow(),0,first_name);
         ui->table_widget_teachers->setItem(ui->table_widget_teachers->currentRow(),1,last_name);
         ui->table_widget_teachers->setItem(ui->table_widget_teachers->currentRow(),2,patronymic);
         ui->table_widget_teachers->setItem(ui->table_widget_teachers->currentRow(),3,salary);
         ui->table_widget_teachers->setItem(ui->table_widget_teachers->currentRow(),4,combo_box);
     }
     delete open_dialogue;
 }
}
}

void MainWindow::function_redrawing_subordinate_table()
{
    ui->table_widget_subordinate->clearContents();
    ui->table_widget_subordinate->setRowCount(0);
    int i =map_sub.values(ui->table_widget_teachers->currentRow()).size()-1;
    if(map_sub.values().size()!=0)
   {
        while(i>=0)
    {
            ui->table_widget_subordinate->insertRow(ui->table_widget_subordinate->rowCount());
             int a=0;
             for(int j=4;j>=0;--j)
           {
           QTableWidgetItem* item = new QTableWidgetItem(map_sub.values(ui->table_widget_teachers->currentRow())[i].value(j));
           ui->table_widget_subordinate->setItem(ui->table_widget_subordinate->rowCount()-1,a,item);
           a++;
           }
             --i;
    }
   }

}

MainWindow::~MainWindow()
{
    delete ui;
}











