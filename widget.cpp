#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //connect(&server, &QTcpServer::newConnection, this, &Widget::connectToServer);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_bind_clicked()
{
    if(!server.listen(QHostAddress::Any, static_cast<quint16>(ui->spinBox_port->value()))){
        qDebug()<<"Error start listen "<<server.errorString();
    }
}

void Widget::on_pushButton_connect_clicked()
{
    QStringList lst = ui->lineEdit_ip_address->text().split(':');
    if(!lst.at(1).trimmed().isEmpty()){
        ServerIP::pushConnection(lst.at(0), lst.at(1).toInt());
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(lst.at(0)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(lst.at(1)));
    }
}

