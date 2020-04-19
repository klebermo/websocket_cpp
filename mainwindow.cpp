#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString message = ui->lineEdit->text();

    connect(&m_webSocket, &QWebSocket::connected, [this, message](){
        QJsonObject object
        {
            {"name", message}
        };
        QJsonDocument d(object);
        m_webSocket.open(QUrl(QStringLiteral("ws://localhost:8080/name")));
        m_webSocket.sendTextMessage(d.toJson().toStdString().c_str());
        m_webSocket.close();
    });
}
