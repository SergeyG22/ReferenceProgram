#include "testingcomponents.h"

TestingComponents::TestingComponents()
{

}

void TestingComponents::check_empty_fields(QString str) {qDebug()<<str+" is empty";}
void TestingComponents::pass_widget_values(int size){ if(size<5){qDebug()<<"widgets_values < 5"; } }
