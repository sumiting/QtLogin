#include "mainwindow.h"
#include <QApplication>
#include "logindlg.h"
#include <QObject>




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
  MainWindow w;
  LoginDlg dlg; //建立自己新建的LoginDlg类的实例dlg

  QObject::connect(&dlg,SIGNAL(sendData(QString)),&w,SLOT(receiveData(QString)));
  if(dlg.exec()==QDialog::Accepted){
     w.show();
     return a.exec();
 }else{
     return 0;
 }
   w.show();
    return a.exec();

}
