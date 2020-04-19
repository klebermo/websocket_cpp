#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onStateChanged(m_webSocket.state());
    connect(&m_webSocket, &QWebSocket::stateChanged, this, &MainWindow::onStateChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    if(ui->connectBtn->text() == "Conectar") {
        m_webSocket.open(QUrl(QStringLiteral("ws://localhost:8080/name")));
    } else {
        m_webSocket.close();
    }
}

void MainWindow::on_sendBtn_clicked()
{
    if(m_webSocket.state() == QAbstractSocket::ConnectedState) {
        QString message = ui->lineEdit->text();
        QJsonObject object
        {
            {"name", message}
        };
        QJsonDocument d(object);
        m_webSocket.sendTextMessage(d.toJson().toStdString().c_str());
    }
}

void MainWindow::onStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        ui->status->setText("CLOSED");
        enableWidgets(false);
        ui->connectBtn->setText("Conectar");
        break;
    case QAbstractSocket::ConnectingState:
        ui->status->setText("CONNECTING");
        break;
    case QAbstractSocket::ConnectedState:
        ui->status->setText("OPENED");
        enableWidgets(true);
        ui->connectBtn->setText("Desconectar");
        break;
    default:
        break;

    }

}

void MainWindow::enableWidgets(bool state)
{
    ui->sendBtn->setEnabled(state);
}

