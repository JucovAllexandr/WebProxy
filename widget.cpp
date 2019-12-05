#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&server, &Server::connectionUpdated, this, &Widget::updateConnections);
    connect(&server, &Server::connectionClosed, this, &Widget::deleteConnection);
    //connect(&server, &QTcpServer::newConnection, this, &Widget::connectToServer);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateConnections(qintptr socketDescriptor, ServerIP::ServerAddress clientIp, ServerIP::ServerAddress serverIp)
{
    bool flag = 0;
    for(int row = 0; row < ui->tableWidget_connections->rowCount(); row++){
        if(ui->tableWidget_connections->item(row, 0)->text().toLongLong() == socketDescriptor){
            ui->tableWidget_connections->item(row, 1)->setText(clientIp.addr.toString()+":"+QString::number(clientIp.port));
            ui->tableWidget_connections->item(row, 2)->setText(serverIp.addr.toString()+":"+QString::number(serverIp.port));
            flag = 1;
            break;
        }
    }

    if(!flag){
        ui->tableWidget_connections->setRowCount(ui->tableWidget_connections->rowCount()+1);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(socketDescriptor));
        QTableWidgetItem *cIp = new QTableWidgetItem(clientIp.addr.toString()+":"+QString::number(clientIp.port));
        QTableWidgetItem *sIp = new QTableWidgetItem(serverIp.addr.toString()+":"+QString::number(serverIp.port));

        ui->tableWidget_connections->setItem(ui->tableWidget_connections->rowCount()-1, 0, id);
        ui->tableWidget_connections->setItem(ui->tableWidget_connections->rowCount()-1, 1, cIp);
        ui->tableWidget_connections->setItem(ui->tableWidget_connections->rowCount()-1, 2, sIp);
    }
}

void Widget::deleteConnection(qintptr socketDescriptor)
{
    for(int row = 0; row < ui->tableWidget_connections->rowCount(); row++){
        if(ui->tableWidget_connections->item(row, 0)->text().toLongLong() == socketDescriptor){
            ui->tableWidget_connections->removeRow(row);
            break;
        }
    }

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

