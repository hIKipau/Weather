#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QPixmap>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void clearValues();
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void readData();
    void finishReading();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QNetworkReply *repoReply;
    QByteArray dataBuffer;
};

#endif // MAINWINDOW_H

