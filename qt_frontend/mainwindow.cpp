#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_btnGetAllPersons_clicked()
{
    QString site_url="http://localhost:3000/example/allpersons";
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    allPersonsManager = new QNetworkAccessManager(this);
    connect(allPersonsManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(allPersonsSlot(QNetworkReply*)));
    allPersonsReply = allPersonsManager->get(request);
}

void MainWindow::allPersonsSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0 || response_data.compare("")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else{
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonArray json_array=json_doc.array();
        QString persons;
        foreach(const QJsonValue &value, json_array){
            QJsonObject json_obj=value.toObject();
            persons+=QString::number((json_obj["id_person"].toInt()))+" "+json_obj["fname"].toString()+" "+json_obj["lname"].toString()+" "+QString::number((json_obj["money"].toDouble()))+"\r\n";
        }
        ui->labelResult->setText(persons);
    }


    allPersonsReply->deleteLater();
    reply->deleteLater();
    allPersonsManager->deleteLater();
}


void MainWindow::on_btnGetOnePerson_clicked()
{
    QString id=ui->lineEditId->text();
    if(id==""){
        ui->labelResult->setText("Anna id!");
    }
    else {
        QString site_url="http://localhost:3000/example/oneperson/"+id;
        QString credentials="automat123:pass123";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
        onePersonManager = new QNetworkAccessManager(this);
        connect(onePersonManager, SIGNAL(finished (QNetworkReply*)),
        this, SLOT(onePersonSlot(QNetworkReply*)));
        onePersonReply = onePersonManager->get(request);
    }

}
void MainWindow::onePersonSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("")==0){
        ui->labelResult->setText("Henkilöä ei löydy");
    }
    else{
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString person=QString::number(json_obj["id_person"].toInt())+" "+json_obj["fname"].toString()+" "+json_obj["lname"].toString()+" "+QString::number(json_obj["money"].toDouble())+ "\r\n";
        ui->labelResult->setText(person);
    }

    onePersonReply->deleteLater();
    reply->deleteLater();
    onePersonManager->deleteLater();
}


void MainWindow::on_btnGetFullname_clicked()
{
    QString id=ui->lineEditId->text();
    QString site_url="http://localhost:3000/example/fullname/"+id;
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    fullnameManager = new QNetworkAccessManager(this);
    connect(fullnameManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(fullnameSlot(QNetworkReply*)));
    fullnameReply = fullnameManager->get(request);
}

void MainWindow::fullnameSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("")==0){
        ui->labelResult->setText("Henkilöä ei löydy");
    }
    else{
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString person=json_obj["fullname"].toString();
        ui->labelResult->setText(person);
    }

    fullnameReply->deleteLater();
    reply->deleteLater();
    fullnameManager->deleteLater();
}


void MainWindow::on_btnRaise_clicked()
{
    QString id=ui->lineEditRaiseId->text();
    QString amount=ui->lineEditRaiseAmount->text();
    QJsonObject json_obj;
    json_obj.insert("id",id);
    json_obj.insert("amount",amount);
    QString site_url="http://localhost:3000/person/money_action";
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    raiseManager = new QNetworkAccessManager(this);
    connect(raiseManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(raiseSlot(QNetworkReply*)));
    raiseReply=raiseManager->post(request, QJsonDocument(json_obj).toJson());
}
void MainWindow::raiseSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->labelResult->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("0")==0){
        ui->labelResult->setText("Nosto ei onnistu");
    }
    else{
        ui->labelResult->setText("Nosto onnistui");
    }
    raiseReply->deleteLater();
    reply->deleteLater();
    raiseManager->deleteLater();
}

void MainWindow::on_lineEditId_textChanged(const QString &arg1)
{
    ui->btnGetFullname->setEnabled(true);
}
