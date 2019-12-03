#include "widget.h"
#include "ui_widget.h"

static inline QString host(const QHttpServerRequest &request)
{
    return request.headers()[QStringLiteral("Host")].toString();
}

static inline QString methodToString(QHttpServerRequest::Method method){
    QString str = "";
    switch (method) {
    case QHttpServerRequest::Method::Get: str = "GET"; break;
    case QHttpServerRequest::Method::Put: str = "PUT"; break;
    case QHttpServerRequest::Method::Post: str = "POST"; break;
    case QHttpServerRequest::Method::Delete: str = "DELETE"; break;
    }

    return str;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    httpServer.route("/", []() {
            return "Hello world";
        });

        httpServer.route("/query", [] (const QHttpServerRequest &request) {
            return QString("%1/query/").arg(host(request));
        });

        httpServer.route("/query/", [] (qint32 id, const QHttpServerRequest &request) {
            return QString("%1/query/%2").arg(host(request)).arg(id);
        });

        httpServer.route("/query/<arg>/log", [] (qint32 id, const QHttpServerRequest &request) {
            return QString("%1/query/%2/log").arg(host(request)).arg(id);
        });

        httpServer.route("/query/<arg>/log/", [] (qint32 id, float threshold,
                                                  const QHttpServerRequest &request) {
            return QString("%1/query/%2/log/%3").arg(host(request)).arg(id).arg(threshold);
        });

        httpServer.route("/user/", [] (const qint32 id) {
            return QString("User %1").arg(id);
        });

        httpServer.route("/user/<arg>/detail", [] (const qint32 id) {
            return QString("User %1 detail").arg(id);
        });

        httpServer.route("/user/<arg>/detail/", [] (const qint32 id, const qint32 year) {
            return QString("User %1 detail year - %2").arg(id).arg(year);
        });

        httpServer.route("/assets/<arg>", [] (const QUrl &url) {
            return QHttpServerResponse::fromFile(QStringLiteral(":/assets/%1").arg(url.path()));
        });

        httpServer.route("/remote_address", [](const QHttpServerRequest &request) {
            return request.remoteAddress().toString();
        });

        const auto port = httpServer.listen(QHostAddress::Any);


        httpServer.route("/www", [](const QHttpServerRequest &request) {
            return methodToString(request.method());
        });

        if (port == -1) {
            qDebug() << QCoreApplication::translate(
                    "QHttpServerExample", "Could not run on http://127.0.0.1:%1/").arg(port);
            return;
        }

        qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Running on http://127.0.0.1:%1/ ").arg(port);
}

Widget::~Widget()
{
    delete ui;
}

