#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QList < QLCDNumber* >  lcdnumbers = findChildren<QLCDNumber*>();

        foreach ( QLCDNumber * lcdnumber, lcdnumbers) {
        //qDebug() << lcdnumber->objectName();
        lcdnumber->display("-------");
        }
    //ui->temp_lcdNumber_1->display("-------");
    //ui->temp_lcdNumber_12->display("-------");

    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";
    serialBuffer = "";
    QStringList bufferSplitTemp=serialBuffer.split(",");


   // qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();

  /* foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts() ){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << " Vendor ID: " << serialPortInfo.vendorIdentifier();
            qDebug() << "port name is : " << serialPortInfo.portName();
            arduino_port_name = serialPortInfo.portName();
        }*/


    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts() ){
               if(serialPortInfo.hasVendorIdentifier()){
                //qDebug() << " Vendor ID: " << seriaPortInfo.vendorIdentifier();
                //qDebug() << "port name is : " << seriaPortInfo.portName();
                arduino_port_name = serialPortInfo.portName();
                //ui->comboBox->addItem(arduino_port_name);
                arduino_is_available = true;
    }
 }
    if(arduino_is_available){
        //open & configure the serial port
        arduino->setPortName(arduino_port_name);
       // arduino->open(QSerialPort::ReadOnly);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

    }
    else{
        //give error message
        QMessageBox::warning(this, "Port error", "Couldn't find the arduino");
    }

   for(int i = 0; i < 12; i++)
       {
           //ui->comboBox->addItem("item " + QString::number(i)); //testing qcombobox converted to string
       ui->comboBox->addItem(QString::number(i));
       }
}


Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void Dialog::readSerial(){
    palette = new QPalette();
    //QString serialBuffer;
        //Get the data from serial, and let MainWindow know it's ready to be collected.
        while(arduino->canReadLine())
        {
            //String for data to go.
            bool parsedCorrectly = 0;
            //characters = "";

            //Loop until we find the newline delimiter.
            do
            {
              //Get the line.
              QByteArray serialData = arduino->readLine();//Line();
               qDebug() << serialData;
              //If we have found a new line character in any line, complete the parse.
              if(QString(serialData).contains('\n'))
              {
                 if(QString(serialData) != "\n")
                  {
                      serialBuffer += QString(serialData);
                      serialBuffer.remove(QRegExp("[\\n\\t\\r]"));
                      parsedCorrectly = 1;
                      qDebug() << serialBuffer;
                      QStringList bufferSplit=serialBuffer.split(";");
                      qDebug() << bufferSplit;
                      qDebug() << bufferSplit[0];
                      qDebug() << bufferSplit[1];

                     // Dialog::updateLCD(bufferSplit[1]);
                     //qDebug() << bufferSplit;
                     if (bufferSplit[1].toFloat() < 8){
                      palette->setColor(QPalette::WindowText, Qt::red);
                     } else{
                      palette->setColor(QPalette::WindowText, Qt::blue);
                     }

                     if ( bufferSplit[0] == "1" ){
                         ui->temp_lcdNumber_1->setPalette(*palette);
                         ui->temp_lcdNumber_1->display(bufferSplit[1]);
                           }

                     if ( bufferSplit[0] == "2" ){
                        ui->temp_lcdNumber_2->setPalette(*palette);
                        ui->temp_lcdNumber_2->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "3" ){
                        ui->temp_lcdNumber_3->setPalette(*palette);
                        ui->temp_lcdNumber_3->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "4" ){
                        ui->temp_lcdNumber_4->setPalette(*palette);
                        ui->temp_lcdNumber_4->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "5" ){
                        ui->temp_lcdNumber_5->setPalette(*palette);
                        ui->temp_lcdNumber_5->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "6" ){
                        ui->temp_lcdNumber_6->setPalette(*palette);
                        ui->temp_lcdNumber_6->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "7" ){
                        ui->temp_lcdNumber_7->setPalette(*palette);
                        ui->temp_lcdNumber_7->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "8" ){
                        ui->temp_lcdNumber_8->setPalette(*palette);
                        ui->temp_lcdNumber_8->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "9" ){
                        ui->temp_lcdNumber_9->setPalette(*palette);
                        ui->temp_lcdNumber_9->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "10" ){
                        ui->temp_lcdNumber_10->setPalette(*palette);
                        ui->temp_lcdNumber_10->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "11" ){
                        ui->temp_lcdNumber_11->setPalette(*palette);
                        ui->temp_lcdNumber_11->display(bufferSplit[1]);
                     }
                     if ( bufferSplit[0] == "12" ){
                        ui->temp_lcdNumber_12->setPalette(*palette);
                        ui->temp_lcdNumber_12->display(bufferSplit[1]);
                     }

                  }
              }
              //If we don't find the newline straight away, add the string we got to the characters QString and keep going.
              else
                  serialBuffer += QString(serialData);
            }while(!parsedCorrectly);

            //Save characters to data and emit signal to collect it.
           // data = characters;


            //Reset characters!
          serialBuffer = "";
        }

                    //instead of multiple if statement
                     /*for (int i = 0; i < list.size(); ++i) {
                         if (list.at(i) == "Jane")
                           cout << "Found Jane at position " << i << endl;
                     }*/



   // serialBuffer = "";
}




void Dialog::updateLCD(const QString sensor_reading){

   //ui->temp_lcdNumber_1->display(sensor_reading);

}
void Dialog::updateContNum(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    } else{
        qDebug() << "couldn't write to serial!";
        QMessageBox::critical(this,"Error","Couldn't write to serial!");
    }

}


void Dialog::on_pushButton_Send_clicked()
{
    Dialog::updateContNum(ui->comboBox->currentText());
}
