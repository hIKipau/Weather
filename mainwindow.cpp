#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
    repoReply = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearValues(){
    ui->cityName->clear();
}

void MainWindow::on_pushButton_clicked()
{
    auto name = ui->cityName->text();
    if(!name.isEmpty()){
        ui->label_2->setText(name);
        clearValues();

        QNetworkRequest request;
        request.setUrl(QUrl("https://api.weatherapi.com/v1/current.json?key=4bbe3be48f2a48e2981195438242109&q=" + name));

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

void MainWindow::readData()
{
    dataBuffer.append(netReply->readAll());
}

void MainWindow::finishReading()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(this, "Error", QString("Request[Error] : %1").arg(netReply->errorString()));
    } else {
        QJsonObject userJsonInfo = QJsonDocument::fromJson(dataBuffer).object();

        QString date = userJsonInfo.value("location").toObject().value("localtime").toString();
        ui->dateSlot->setText(date);

        double temperature = userJsonInfo.value("current").toObject().value("temp_c").toDouble();
        ui->temperatureSlot->setText(QString::number(temperature));

        dataBuffer.clear();
    }
}
