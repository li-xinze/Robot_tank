#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QTimer>
#include <QDebug>
#include <QAbstractSocket>
class QTcpSocket;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();


private slots:
    void sendmessage();
    void on_pushButton_clicked();
    void showMsg(QString);
    void openJoy();
    void joyMove();
    int  calcPos(unsigned int);
    void clear_color();
    void newConnect();


private:
    bool flag;
    QTcpSocket *tcpSocket;
    Ui::MainWindow *ui;
    QString JOY_R,JOY_U;
    QTimer *timer;
     QTimer *timer2;
    unsigned int joyXPos, joyYPos, joyZPos, joyRPos, joyUPos, joyVPos, numButtons, numAxes, period;
    int joyX, joyY, joyZ, joyR, joyU, joyV;
    bool hasU, hasV;
};

#endif // MAINWINDOW_H
