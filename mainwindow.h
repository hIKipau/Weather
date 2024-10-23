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
#include <QSqlQuery>

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
    ~MainWindow();



private slots:

    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QNetworkReply *repoReply;
    QByteArray dataBuffer;
    QString name;
    void connectToDatabase(); // Объявление функции
    void readData();
    void finishReading();
    void clearValues();
    void makeRequest();
    void insertWeatherData(const QString& name, const QString& region, const QString& country,
                           const QDateTime& localtime, double temp_c, double wind_kph,
                           double pressure_mb, double precip_mm, int humidity,
                           int cloud, double feelslike_c, double windchill_c,
                           double heatindex_c, double dewpoint_c, double vis_km,
                           double gust_kph);

    QDate currentDate;
    QTime currentTime;
    QSqlQuery query;



};

#endif // MAINWINDOW_H

