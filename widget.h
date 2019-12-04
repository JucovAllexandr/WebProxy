#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "serverip.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    Server server;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:


    void on_pushButton_bind_clicked();

    void on_pushButton_connect_clicked();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
