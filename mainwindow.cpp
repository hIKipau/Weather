#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QInputDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QDateTime>
#include <QTimer>
#include <QWidget>
#include <qwidget.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connectToDatabase();


    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
    repoReply = nullptr;

    QLabel* backgroundLabel = new QLabel(this);
    QPixmap background(":/Resources/photo/фон.png");
    backgroundLabel->setPixmap(background.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();

    currentDate = QDate::currentDate();
    currentTime = QTime::currentTime();
}

void MainWindow::connectToDatabase() {
    // Удалим существующее соединение, если оно есть
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    // Проверяем наличие драйвера
    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        qDebug() << "PostgreSQL driver is not available!";
        QMessageBox::critical(this, "Error", "PostgreSQL driver is not available!");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "MainConnection");
    db.setHostName("b3kx6uueuipmazx6lbs4-postgresql.services.clever-cloud.com");
    db.setDatabaseName("b3kx6uueuipmazx6lbs4");
    db.setUserName("ufyrbpr5pxga8b0eiwhg");
    db.setPassword("QPu4Hea5Cg2Fs9JICUFa4vjY7IlF78");
    db.setPort(50013);

    // Подробная проверка подключения
    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        qDebug() << "Database Error Type:" << db.lastError().type();
        qDebug() << "Database Driver:" << db.driverName();
        qDebug() << "Database Connection Name:" << db.connectionName();
        QMessageBox::critical(this, "Database Error",
                              "Cannot open database: " + db.lastError().text());
        return;
    }

    qDebug() << "Database connected successfully!";

    // Проверка создания таблицы
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS WeatherData ("
                    "id SERIAL PRIMARY KEY,"
                    "name VARCHAR(255),"
                    "region VARCHAR(255),"
                    "country VARCHAR(255),"
                    "local_time TIMESTAMP,"
                    "temp_c DOUBLE PRECISION,"
                    "wind_kph DOUBLE PRECISION,"
                    "pressure_mb DOUBLE PRECISION,"
                    "precip_mm DOUBLE PRECISION,"
                    "humidity INTEGER,"
                    "cloud INTEGER,"
                    "feelslike_c DOUBLE PRECISION,"
                    "windchill_c DOUBLE PRECISION,"
                    "heatindex_c DOUBLE PRECISION,"
                    "dewpoint_c DOUBLE PRECISION,"
                    "vis_km DOUBLE PRECISION,"
                    "gust_kph DOUBLE PRECISION"
                    ")")) {
        qDebug() << "Error creating table:" << query.lastError().text();
    } else {
        qDebug() << "Table created or already exists";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void checkDatabaseDrivers() {
    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available database drivers:" << drivers;
}


void MainWindow::makeRequest()
{

    if (!name.isEmpty()) {
        ui->label_2->setText(name);

        QNetworkRequest request;
        QString timestamp = QString::number(QDateTime::currentSecsSinceEpoch());
        request.setUrl(QUrl("https://api.weatherapi.com/v1/current.json?key=4bbe3be48f2a48e2981195438242109&q=" + name + "&t=" + timestamp));

#if QT_VERSION >= QT_VERSION_CHECK(6, 7, 1)
        if (request.url().scheme().toLower() == QLatin1String("https")) {
            request.setAttribute(QNetworkRequest::Http2AllowedAttribute, true);
        }
#endif

        netReply = netManager->get(request);
        connect(netReply, &QNetworkReply::readyRead, this, &MainWindow::readData);
        connect(netReply, &QNetworkReply::finished, this, &MainWindow::finishReading);
    }
}



void MainWindow::clearValues()
{
    ui->cityName->clear();
}

void MainWindow::on_pushButton_clicked()
{
    name = ui->cityName->text().trimmed().toLower();
    if (!name.isEmpty()) {

        makeRequest();
    }
    qDebug() << name;
    checkDatabaseDrivers();
}

void MainWindow::readData()
{
    dataBuffer.append(netReply->readAll());
}

void MainWindow::insertWeatherData(const QString& name, const QString& region,
                                   const QString& country, const QDateTime& localtime, double temp_c,
                                   double wind_kph, double pressure_mb, double precip_mm, int humidity,
                                   int cloud, double feelslike_c, double windchill_c, double heatindex_c,
                                   double dewpoint_c, double vis_km, double gust_kph) {

    QSqlDatabase db = QSqlDatabase::database("MainConnection");

    if (!db.isValid()) {
        qDebug() << "Database connection is invalid!";
        return;
    }

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        if (!db.open()) {
            qDebug() << "Failed to reopen database:" << db.lastError().text();
            return;
        }
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO WeatherData "
                  "(name, region, country, local_time, temp_c, wind_kph, pressure_mb, "
                  "precip_mm, humidity, cloud, feelslike_c, windchill_c, heatindex_c, "
                  "dewpoint_c, vis_km, gust_kph) "
                  "VALUES (:name, :region, :country, :localtime, :temp_c, :wind_kph, "
                  ":pressure_mb, :precip_mm, :humidity, :cloud, :feelslike_c, "
                  ":windchill_c, :heatindex_c, :dewpoint_c, :vis_km, :gust_kph)");

    query.bindValue(":name", name);
    query.bindValue(":region", region);
    query.bindValue(":country", country);
    query.bindValue(":localtime", localtime);
    query.bindValue(":temp_c", temp_c);
    query.bindValue(":wind_kph", wind_kph);
    query.bindValue(":pressure_mb", pressure_mb);
    query.bindValue(":precip_mm", precip_mm);
    query.bindValue(":humidity", humidity);
    query.bindValue(":cloud", cloud);
    query.bindValue(":feelslike_c", feelslike_c);
    query.bindValue(":windchill_c", windchill_c);
    query.bindValue(":heatindex_c", heatindex_c);
    query.bindValue(":dewpoint_c", dewpoint_c);
    query.bindValue(":vis_km", vis_km);
    query.bindValue(":gust_kph", gust_kph);

    if (!query.exec()) {
        qDebug() << "Insert error:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();

        // Вывод привязанных значений
        const QList<QVariant>& boundValues = query.boundValues();
        for(int i = 0; i < boundValues.size(); ++i) {
            qDebug() << "Value" << i << ":" << boundValues.at(i);
        }
    } else {
        qDebug() << "Data inserted successfully";
    }
}

void MainWindow::finishReading() {
    if (netReply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << netReply->errorString();
        QMessageBox::warning(this, "Error", QString("Request[Error]: %1").arg(netReply->errorString()));
    } else {
        QJsonObject userJsonInfo = QJsonDocument::fromJson(dataBuffer).object();

        QString name = userJsonInfo.value("location").toObject().value("name").toString();
        QString region = userJsonInfo.value("location").toObject().value("region").toString();
        QString country = userJsonInfo.value("location").toObject().value("country").toString();
        QString localtimeString = userJsonInfo.value("location").toObject().value("localtime").toString();
        QDateTime localtime = QDateTime::fromString(localtimeString, "yyyy-MM-dd HH:mm");

        double temperature = userJsonInfo.value("current").toObject().value("temp_c").toDouble();
        double wind_kph = userJsonInfo.value("current").toObject().value("wind_kph").toDouble();
        double pressure_mb = userJsonInfo.value("current").toObject().value("pressure_mb").toDouble();
        double precip_mm = userJsonInfo.value("current").toObject().value("precip_mm").toDouble();
        int humidity = userJsonInfo.value("current").toObject().value("humidity").toInt();
        int cloud = userJsonInfo.value("current").toObject().value("cloud").toInt();
        double feelslike_c = userJsonInfo.value("current").toObject().value("feelslike_c").toDouble();
        double windchill_c = userJsonInfo.value("current").toObject().value("windchill_c").toDouble();
        double heatindex_c = userJsonInfo.value("current").toObject().value("heatindex_c").toDouble();
        double dewpoint_c = userJsonInfo.value("current").toObject().value("dewpoint_c").toDouble();
        double vis_km = userJsonInfo.value("current").toObject().value("vis_km").toDouble();
        double gust_kph = userJsonInfo.value("current").toObject().value("gust_kph").toDouble();

        // Вставка данных в базу
        insertWeatherData(name, region, country, localtime, temperature, wind_kph,
                          pressure_mb, precip_mm, humidity, cloud,
                          feelslike_c, windchill_c, heatindex_c,
                          dewpoint_c, vis_km, gust_kph);

        // Обновление UI или другие действия
        ui->dateSlot->setText(localtime.toString());
        ui->temperatureSlot->setText(QString::number(temperature));

        dataBuffer.clear();
    }

    netReply->deleteLater();  // Удаляем объект ответа
}
