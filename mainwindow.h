#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebSockets/QtWebSockets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectBtn_clicked();
    void on_sendBtn_clicked();
    void onStateChanged(QAbstractSocket::SocketState state);
private:
    Ui::MainWindow *ui;
    QWebSocket m_webSocket;
    void enableWidgets(bool state);
};
#endif // MAINWINDOW_H
