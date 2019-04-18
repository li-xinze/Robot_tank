#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JOYSTICK.h"
#include <QMessageBox>
#include <QtNetwork>


#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(joyMove()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(sendmessage()));
    tcpSocket = new QTcpSocket(this);
    joyXPos = 0;
    joyYPos = 0;
    joyZPos = 0;
    joyRPos = 0;
    joyUPos = 0;
    joyVPos = 0;
    joyX = 0;
    joyY = 0;
    joyZ = 0;
    joyR = 0;
    joyU = 0;
    joyV = 0;
    hasV = false;
    numButtons = 0;
    numAxes = 0;

}

MainWindow::~MainWindow()
{
    qJoyReleaseCapture(JOYSTICKID1);

    delete ui;
}
void MainWindow::newConnect()
{

    tcpSocket->abort();
    tcpSocket->connectToHost("39.105.70.124",
                             6001);
    flag = false;
    sendmessage();
}
void MainWindow::sendmessage(){
    int joyu=abs(joyU);
    int joyr=abs(joyR);
    int joyx=abs(joyX);
    if((joyu>3)||(joyr>3)){
        flag =true;
    QByteArray byte;
    float linear_speed = 0.4*joyR/100;
    float angular_speed = 0.5*(joyU/50.0);
    JOY_U = QString::number(-angular_speed);
    JOY_R =QString::number(-linear_speed);
    QString message = JOY_R+","+JOY_U+","+"0.0"+",";
    byte = message.toUtf8();
    tcpSocket->write(byte);
    }
    else if(joyx>4){
        flag = true;
        QByteArray byte;
        JOY_R = "0.0";
        float angular_speed = 0.5*(joyX/50.0);
        JOY_U = QString::number(-angular_speed);
        QString message = JOY_R+","+JOY_U+","+"0.0"+",";
        byte = message.toUtf8();
        tcpSocket->write(byte);
    }
    else{
        if(flag == true){
        QString message = "0.0,0.0,0.0,0.0,";
        QByteArray byte = message.toUtf8();
        tcpSocket->write(byte);
        flag = false;
        }

    }
}

void MainWindow::showMsg(QString str){
    ui->label->setText(str);
}

void MainWindow::openJoy(){
    unsigned int num = qJoyGetNumDevs();
    if(num <= 0){
        showMsg(tr("System doesn't support Joystick."));
        return;
    }
    qDebug()<<"qJoyGetNumDevs="<<num;

    JOYCAPS joycaps;
    UINT size = (UINT)sizeof(joycaps);
    qJoyGetDevCaps(JOYSTICKID1, &joycaps, size); // run err
    numButtons = joycaps.wNumButtons;
    qDebug()<<"qJoyGetDevCaps="<<numButtons;

    numAxes = joycaps.wNumAxes;
    qDebug()<<"joycaps.wNumAxes="<<numAxes;

    unsigned int caps = joycaps.wCaps;
    qDebug()<<"joycaps.wCaps="<<caps;
    if(caps & JOYCAPS_HASZ) qDebug()<<"hasZ";
    if(caps & JOYCAPS_HASR) qDebug()<<"hasR";
    if(caps & JOYCAPS_HASU) {hasU = true;qDebug()<<"hasU";}
    if(caps & JOYCAPS_HASV) {hasV = true;qDebug()<<"hasV";}

    if(caps & JOYCAPS_HASPOV) qDebug()<<"hasPOV";
    if(caps & JOYCAPS_POV4DIR) qDebug()<<"POV4DIR";
    if(caps & JOYCAPS_POVCTS) qDebug()<<"POVCTS";

    timer->start(period);
    timer2->start(50);
}

void MainWindow::clear_color(){
    ui->PB_Y1->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_B2->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_A3->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_X4->setStyleSheet("color: rgb(0, 0, 0);");

    ui->PB_F->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_B->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_R->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_L->setStyleSheet("color: rgb(0, 0, 0);");

    ui->PB_L1->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_R1->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_L2->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_R2->setStyleSheet("color: rgb(0, 0, 0);");

    ui->PB_F->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_B->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_R->setStyleSheet("color: rgb(0, 0, 0);");
    ui->PB_L->setStyleSheet("color: rgb(0, 0, 0);");
}
bool motor =false;
bool lidar = false;

void MainWindow::joyMove(){ // Joystick button action or
    JOYINFOEX joyInfoEx;
    joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX));
    joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS;
    qJoyGetPosEx(JOYSTICKID1, &joyInfoEx);
    if(joyInfoEx.dwButtonNumber){
        qDebug()<<"joyInfoEx.dwButtonNumber="<<joyInfoEx.dwButtonNumber;//总是为1
        QByteArray byte;
        QString message;
        switch(joyInfoEx.dwButtons){
            case JOY_BUTTON1:
             message = "0.0,0.0,9.0,";
             byte = message.toUtf8();
             tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON1");
                 clear_color();
                 ui->PB_Y1->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON2:
             message = "0.0,0.0,10.0,";
             byte = message.toUtf8();
             tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON2");
                 clear_color();
                 ui->PB_B2->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON3:
            message = "0.0,0.0,3.0,";
            byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON3");
                 clear_color();
                 ui->PB_A3->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON4:
            message = "0.0,0.0,4.0,";
            byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON4");
                 clear_color();
                 ui->PB_X4->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON5:
            message = "0.0,0.0,6.0,";
            byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON5");
                 clear_color();
                 ui->PB_L1->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON6:
            message = "0.0,0.0,8.0,";
            byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
                 ui->lineEdit_2->setText("JOY_BUTTON6");
                 clear_color();
                 ui->PB_R1->setStyleSheet("color: rgb(255, 0, 0);");
                 break;
            case JOY_BUTTON7:
                 ui->lineEdit_2->setText("JOY_BUTTON7");
                 clear_color();
                 ui->PB_L2->setStyleSheet("color: rgb(255, 0, 0);");
                 message = "0.0,0.0,1,";
                 byte = message.toUtf8();
                 tcpSocket->write(byte);
                 tcpSocket->write(byte);
                 tcpSocket->write(byte);
                 break;
            case JOY_BUTTON8:
                 ui->lineEdit_2->setText("JOY_BUTTON8");
                 clear_color();
                 ui->PB_R2->setStyleSheet("color: rgb(255, 0, 0);");

                     message = "0.0,0.0,2,";
                     byte = message.toUtf8();
                     tcpSocket->write(byte);
                     tcpSocket->write(byte);
                     tcpSocket->write(byte);

                 break;
            //没有下面的
           case JOY_BUTTON9:
             ui->lineEdit_2->setText("JOY_BUTTON9");
             clear_color();
             ui->PB_R1->setStyleSheet("color: rgb(255, 0, 0);");
             break;
            case JOY_BUTTON10: ui->lineEdit_2->setText("JOY_BUTTON10"); break;
            case JOY_BUTTON11: ui->lineEdit_2->setText("JOY_BUTTON11"); break;
            case JOY_BUTTON12: ui->lineEdit_2->setText("JOY_BUTTON12"); break;
            case JOY_BUTTON13: ui->lineEdit_2->setText("JOY_BUTTON13"); break;
            case JOY_BUTTON14: ui->lineEdit_2->setText("JOY_BUTTON14"); break;
            case JOY_BUTTON15: ui->lineEdit_2->setText("JOY_BUTTON15"); break;
            case JOY_BUTTON16: ui->lineEdit_2->setText("JOY_BUTTON16"); break;
            case JOY_BUTTON17: ui->lineEdit_2->setText("JOY_BUTTON17"); break;
            case JOY_BUTTON18: ui->lineEdit_2->setText("JOY_BUTTON18"); break;
            case JOY_BUTTON19: ui->lineEdit_2->setText("JOY_BUTTON19"); break;
            case JOY_BUTTON20: ui->lineEdit_2->setText("JOY_BUTTON20"); break;
            case JOY_BUTTON21: ui->lineEdit_2->setText("JOY_BUTTON21"); break;
            case JOY_BUTTON22: ui->lineEdit_2->setText("JOY_BUTTON22"); break;
            case JOY_BUTTON23: ui->lineEdit_2->setText("JOY_BUTTON23"); break;
            case JOY_BUTTON24: ui->lineEdit_2->setText("JOY_BUTTON24"); break;
            case JOY_BUTTON25: ui->lineEdit_2->setText("JOY_BUTTON25"); break;
            case JOY_BUTTON26: ui->lineEdit_2->setText("JOY_BUTTON26"); break;
            case JOY_BUTTON27: ui->lineEdit_2->setText("JOY_BUTTON27"); break;
            case JOY_BUTTON28: ui->lineEdit_2->setText("JOY_BUTTON28"); break;
            case JOY_BUTTON29: ui->lineEdit_2->setText("JOY_BUTTON29"); break;
            case JOY_BUTTON30: ui->lineEdit_2->setText("JOY_BUTTON30"); break;
            case JOY_BUTTON31: ui->lineEdit_2->setText("JOY_BUTTON31"); break;
            case JOY_BUTTON32: ui->lineEdit_2->setText("JOY_BUTTON32"); break;

            default: ui->lineEdit->setText("null");
        }
    }
    if(1){ // hasPov
        switch(joyInfoEx.dwPOV){
            case JOY_POVCENTERED:
                ui->lineEdit->setText("JOY_POVCENTERED.");
                break;
            case JOY_POVFORWARD:
                ui->lineEdit->setText("JOY_POVFORWARD.");
                clear_color();
                ui->PB_F->setStyleSheet("color: rgb(255, 0, 0);");
                break;
            case JOY_POVRIGHT:
                ui->lineEdit->setText("JOY_POVRIGHT.");
                clear_color();
                ui->PB_R->setStyleSheet("color: rgb(255, 0, 0);");
                break;
            case JOY_POVBACKWARD:
                ui->lineEdit->setText("JOY_POVBACKWARD.");
                clear_color();
                ui->PB_B->setStyleSheet("color: rgb(255, 0, 0);");
                break;
            case JOY_POVLEFT:
                ui->lineEdit->setText("JOY_POVLEFT.");
                clear_color();
                ui->PB_L->setStyleSheet("color: rgb(255, 0, 0);");
                break;
        }
    }

    QString str;
    unsigned int pos;
// X - OK
    pos = (unsigned int)joyInfoEx.dwXpos;
    if(joyXPos != pos){
        joyXPos = pos;
        joyX = calcPos(joyXPos);
        str = "\nX=" + QString::number(joyX, 'f', 0);
        qDebug()<<str;
        ui->lineEdit_3->setText(str);
        ui->LE_X->setText(QString::number(joyX));
        ui->LE_XX->setText(QString::number(joyX));
    }
// Y - OK
    pos = (unsigned int)joyInfoEx.dwYpos;
    if(joyYPos != pos){
        joyYPos = pos;
        joyY = calcPos(joyYPos);

        str.append("\nY=" + QString::number(joyY, 'f', 0));
        ui->lineEdit_3->setText(str);

        ui->LE_Y->setText(QString::number(joyY));
        ui->LE_YY->setText(QString::number(joyY));
    }
    /////
    pos = (unsigned int)joyInfoEx.dwZpos;
    if(joyYPos != pos){
        joyYPos = pos;
        joyZ = calcPos(joyYPos);
        if(joyZ<0){
            QString message = "0.0,0.0,5.0,";
            QByteArray byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
        }
        else if(joyZ>0){
            QString message = "0.0,0.0,7.0,";
            QByteArray byte = message.toUtf8();
            tcpSocket->write(byte);
            tcpSocket->write(byte);
            tcpSocket->write(byte);
        }
    }
// R - OK
    pos = (unsigned int)joyInfoEx.dwRpos;
    if(joyRPos != pos){
        joyRPos = pos;
        joyR = calcPos(joyRPos);
        str.append("\nR=" + QString::number(joyR, 'f', 0));
        ui->lineEdit_3->setText(str);

        ui->LE_R->setText(QString::number(joyR));
        ui->LE_RR->setText(QString::number(joyR));
    }


        pos = (unsigned int)joyInfoEx.dwUpos;
        if(joyUPos != pos){
            joyUPos = pos;
            joyU = calcPos(joyUPos);
            str.append("\nU=" + QString::number(joyU, 'f', 0));
            ui->lineEdit_3->setText(str);
            ui->LE_Z->setText(QString::number(joyU));
            ui->LE_ZZ->setText(QString::number(joyU));
        }
//
//    }
//    // V programming has problem
//    if(hasV){
//        pos = (unsigned int)joyInfoEx.dwVpos;
//        if(joyVPos != pos){
//            joyVPos = pos;
//            joyV = calcPos(joyVPos);
//        }
//       str.append("\nV=" + QString::number(joyV, 'f', 0) );
//       ui->label_7->setText(str);
//    }

}



int MainWindow::calcPos(unsigned int joyPos){
    double x = 0;
    x = ((double)joyPos - POS_CENTER)*100 / (POS_MAX - POS_MIN);
    return (int)x;
}



void MainWindow::on_pushButton_clicked()
{
    newConnect();
    openJoy();

}
