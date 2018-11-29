#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include "logindlg.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveData(QString data){
    ui->label_3->setText(data);
}

int ToushiFlag=0;
void MainWindow::on_checkBox_stateChanged(int arg1)
{   if(ToushiFlag==0){
     QMessageBox::about(NULL,"已开启","已开启内容");
     ToushiFlag=1;
    }else{
        QMessageBox::about(NULL,"已取消","已取消内容");
        ToushiFlag=0;
    }


}
