#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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
    void on_btnGetAllPersons_clicked();
    void allPersonsSlot(QNetworkReply *reply);
    void onePersonSlot(QNetworkReply *reply);
    void fullnameSlot(QNetworkReply *reply);

    void on_btnGetOnePerson_clicked();

    void on_btnGetFullname_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *allPersonsManager;
    QNetworkReply *allPersonsReply;

    QNetworkAccessManager *onePersonManager;
    QNetworkReply *onePersonReply;


    QNetworkAccessManager *fullnameManager;
    QNetworkReply *fullnameReply;

};
#endif // MAINWINDOW_H
