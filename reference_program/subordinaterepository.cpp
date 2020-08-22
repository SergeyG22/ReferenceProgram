#include "subordinaterepository.h"

SubordinateRepository::SubordinateRepository(QWidget* pointer_widget):QDialog(pointer_widget, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    table = new QTableWidget;
}


void SubordinateRepository::create(QTableWidget* table_pointer,QStringList table_headers)
{
    QColor color;
    color.setRgb(0,255,255);
    QPalette paint = QPalette();
    paint.setColor(QPalette::Background,color);
    QDialog::setWindowTitle("Добавить подчиненного");
    QDialog::setFixedSize(322,300);
    QDialog::setPalette(paint);
    button_ok = new QPushButton("Добавить");
    button_cancel = new QPushButton("Отменить");
    table->setColumnCount(3);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<table_pointer->rowCount();++i)
    {
     table->insertRow(table->rowCount());
     for(int j=0;j<3;++j) {QTableWidgetItem* widget = new QTableWidgetItem(table_pointer->item(i,j)->text()); table->setItem(i,j,widget);}
    }
    for(auto i=0;i<=4;++i){table->setHorizontalHeaderItem(i,new QTableWidgetItem(table_headers[i]));}
    layout = new QGridLayout;
    layout->addWidget(table);
    layout->addWidget(button_ok,1,0);
    layout->addWidget(button_cancel,2,0);
    layout->setAlignment(Qt::AlignHCenter);
    connect(button_ok,&QPushButton::clicked,this,&SubordinateRepository::accept);
    connect(button_cancel,&QPushButton::clicked,this,&SubordinateRepository::reject);
    QDialog::setLayout(layout);
}

