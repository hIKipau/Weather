#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QInputDialog>
#include <QMessageBox>
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
    repoReply = nullptr;



//     QMediaPlayer *player = new QMediaPlayer;
//     QVideoWidget *videoWidget = new QVideoWidget;

//     player->setVideoOutput(videoWidget);
// player->setSource(QUrl("qrc:/Resources/videos/фон.mp4"));    player->play();
//     QVBoxLayout *layout = new QVBoxLayout;
//     layout->addWidget(videoWidget);

//     QWidget *centralWidget = new QWidget(this);
//     centralWidget->setLayout(layout);
//     setCentralWidget(centralWidget);
//     videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
//     videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//     videoWidget->show();
    QLabel* backgroundLabel = new QLabel(this);
    QPixmap background(":/Resources/photo/фон.png");
    backgroundLabel->setPixmap(background.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());  // Устанавливаем размеры QLabel по всему окну
        backgroundLabel->lower();  // Помещаем QLabel на задний план



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
