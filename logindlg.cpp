#include "logindlg.h"
#include "ui_logindlg.h"
#include <QString>
#include <QMessageBox>
#include <windows.h>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>
#include <string>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <QVBoxLayout>
LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉窗口标题栏
    

    ui->setupUi(this);

}

LoginDlg::~LoginDlg()
{
    delete ui;
}
QJsonObject getJsonObjectFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
QString ConnectMysql(QString username,QString pass){

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("cf");
    db.setUserName("root");
    db.setPassword("root");
    if(!db.open()){
        qDebug()<<"Failed to connect to root mysql admin";
}
    else{
        qDebug()<<"open";
                 }
    QSqlQuery query(db);
    username="name";
    pass="pass";
    query.exec("select gameInfo from userinfor where name="+username+" and pass="+pass+" limit 1");
    query.next();
    //qDebug() << query.value(0).toInt()<< query.value(1).toString()<<query.value(2).toString();
     //qint32 endtime;
     QJsonObject gameInfo=getJsonObjectFromString((query.value(0)).toString());
     QString timestr= (gameInfo.take("cf")).toString();
     //int time = atoi(timestr.c_str());
     //int times = atoi(timestr.ascii());
      long long endtime;
     endtime=timestr.toLongLong();

     qDebug()<<"用户到期时间:"<<endtime<<timestr;

     QDateTime timeNow = QDateTime::currentDateTime();   //获取当前时间
     int timeT = timeNow.toTime_t();
     qDebug()<<"当前时间:"<<timeT;

     if(timeT>endtime){
         return NULL;
     }
     if(endtime==NULL || endtime==0){
         return NULL;
     }
     QDateTime time_1= QDateTime::fromTime_t(endtime);
     qDebug()<<time_1;
     QString etime=time_1.toString();
     QStringList etimel=etime.split(" ");
     QString etime2=etimel[4]+"/"+etimel[1]+etimel[2]+"/"+etimel[3];
     return etime2;

}


//


void LoginDlg::on_pushButton_3_clicked()
{
   QString username=ui->lineEdit->text();
   qDebug()<<username;
   QString pass=ui->lineEdit_2->text();
   QString etime=ConnectMysql(username,pass);
   qDebug()<<"结束时间为"+etime;
   emit sendData(etime);
   if(etime==NULL){
       QMessageBox::warning(this,"警告!","用户名或密码错误或余额不足\n售后群11111",QMessageBox::Yes);

   }else{
       accept();
   }

}

void LoginDlg::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.baidu.com"));
}

void LoginDlg::on_pushButton_2_clicked()
{
    this->close();
}
