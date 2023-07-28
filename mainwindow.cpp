#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QSerialPort serial, s2;
    serial.setPortName("/dev/ttys001");
    s2.setPortName("/dev/ttys002");


    // Open the serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

    }

    if (!s2.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

    }
    qDebug () << serial.isOpen() << " " << s2.isOpen();



    serial.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    s2.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    s2.setDataBits(QSerialPort::Data8);
    s2.setParity(QSerialPort::NoParity);
    s2.setStopBits(QSerialPort::OneStop);
    s2.setFlowControl(QSerialPort::NoFlowControl);


    qDebug() << "Serial port opened.Port name is " << ""<<" Sending and receiving data...";



    qDebug() << serial.isOpen() << s2.isOpen();
    connect (&this->s2, SIGNAL(readyRead()), this, SLOT(DoStuff()));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendSerialData(){

};


void MainWindow::on_pushButton_clicked()
{

    QStringList x;
    QStringList y;

    QString text = this->ui->m1s->text();
    QString text2 = this->ui->m1s2->text();



    QString text3 = this->ui->m2s->text();
    QString text4 = this->ui->m2s2->text();



    x={text,",",text2,","};
    y={text3,",",text4};



    qDebug() << "Oluşturulan Dizi X:";
        for (int i=0;i<x.size();i++ ) {
        qDebug() << x[i];
    }


    qDebug() << "Oluşturulan Dizi Y:";
        for (int i=0;i<y.size();i++ ) {
        qDebug() << y[i];
    }




    // Send data to the serial port
  //  QStringList sendData = x;

    QByteArray output;

    // inputArray - your QStringList
    foreach (const QString &str, x)
    {
        output.append(str.toUtf8());
    }





    // Send data to the serial port
   // QStringList sendData2 = y;

    QByteArray output2;

    // inputArray - your QStringList
    foreach (const QString &str, y)
    {
        output2.append(str.toUtf8());
    }


    qint64 bytesWritten = serial.write(output);
    qint64 bytesWritten2 = serial.write(output2);


    qDebug()<<"writed x data: "<<output;
    qDebug()<<"writed y data: "<<output2;

    if (bytesWritten == -1 && bytesWritten2==-1) {
        qDebug() << "Failed to write data:" << serial.errorString();
    } else {
        qDebug() << "Data sent successfully Bytes written: " << bytesWritten;

    }


    // Read data from the serial port
    QByteArray data;

    while (s2.waitForReadyRead(100)) { // Wait for data to be available for 100 milliseconds
        data = s2.readAll();
      //  qDebug()<<"FERGRE:"<<data;
    }


}




