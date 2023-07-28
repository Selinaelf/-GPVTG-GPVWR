#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QApplication>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void parseMessage(const QList<QByteArray> &fields) {
        static int i= 0;
        qDebug () << "PARSE GPVTG RUBNED " << i;
        ++i;
        qDebug() << "SIZE " << fields.size();

        for(auto &x : fields) {
            qDebug () << "GELDİ " << x;
        }

        if (fields.size() ==4) {
            qDebug()<<"geldim";
            QByteArray VTGid = fields.at(0);
            QByteArray VTGtime = fields.at(1);
            QByteArray VWRid = fields.at(2);
            QByteArray VWRtime = fields.at(3);
            //            QByteArray longitude = fields.at(5);
            //            QByteArray speed = fields.at(7);
            //            QByteArray course = fields.at(8);
            //            QByteArray date = fields.at(9);
            //            QByteArray magneticVariation = fields.at(10);


            this->ui->m1r1->setText(VTGid);
            this->ui->m1r2->setText(VTGtime);

            this->ui->m2r->setText(VWRid);
            this->ui->m2r2->setText(VWRtime);
            //            qDebug() << "Latitude:" << latitude;
            //            qDebug() << "Longitude:" << longitude;
            //            qDebug() << "Speed:" << speed;
            //            qDebug() << "Course:" << course;
            //            qDebug() << "Date:" << date;
            //            qDebug() << "Magnetic Variation:" << magneticVariation;
        }



        else {
            qDebug() << "Invalid GPRMC sentence!";
        }
    };




    // Function to parse NMEA messages
    void parseNmeaMessage(const QByteArray &message) {
        qDebug()<<"HEREr";
        if (message.startsWith('$')) {
            QList<QByteArray> fields = message.mid(1).split(',');
            QByteArray sentenceIdentifier = fields.at(0);

            // Parse NMEA sentences based on sentenceIdentifier
            if (sentenceIdentifier == "GPVTG") {
                parseMessage(fields); // Call the parseGPRMC function to handle the GPRMC sentence
            }


            else {
                qDebug() << "Unsupported NMEA Sentence:" << sentenceIdentifier;
                qDebug() << "Data fields:" << fields;
            }
        }

    }


private slots:
    void on_pushButton_clicked();
    void sendSerialData();

public slots:
    void DoStuff ()
    {
        qDebug() << "IN WHILE";
        QByteArray data2 = s2.readAll();
        QByteArray data3 = s2.readAll();
        // Process the received data (split NMEA messages and handle each one)
        qDebug()<<"received data: "<<data2;
        qDebug() << "IN WHILE";

       parseNmeaMessage(data2); // Pass the full NMEA sentence for parsing

    }



private:
    Ui::MainWindow *ui;
    // QSerialPort *serial;
    QSerialPort serial;
    QSerialPort s2;
};
#endif // MAINWINDOW_H

