#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QString>
namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:

    explicit LoginDlg(QWidget *parent = 0);
    QString etime;
    ~LoginDlg();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sendData(QString);
private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
