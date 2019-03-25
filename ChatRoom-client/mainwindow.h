#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void on_connected();
    void on_disconnected();
    void on_readyRead();

private slots:
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;
    quint16 defaultPort = 1729;
    QTcpSocket *socket;
    bool isConnected = false;

    void setConnectInputsEnabled(bool val);
    void setChatControlsEnabled(bool val);
    void setStatus(QString status, QColor color = Qt::black);
};

#endif // MAINWINDOW_H
