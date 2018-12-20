#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle(QString("ZMigrate Launcher"));

    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    QString zaddress = ui->zaddresslineEdit->text().trimmed();
    QString coin = ui->coinlineEdit->text().trimmed();
    QString command = "zmigrate.exe " + coin + " " + zaddress;
    QString zmigrate_binary = "zmigrate.exe";
    QString komodocli_binary = "komodo-cli.exe";

    bool komodocliExists = QFileInfo::exists(komodocli_binary) && QFileInfo(komodocli_binary).isFile();
    bool zmigrateExists = QFileInfo::exists(zmigrate_binary) && QFileInfo(zmigrate_binary).isFile();

    //qDebug() << "Coin: " + coin << "," << "ZAddress: " + zaddress;
    if (!(coin.isEmpty() || zaddress.isEmpty())) {
        if (zaddress.left(2) == QString("zs")) {
            if (komodocliExists && zmigrateExists) {
                ui->statusBar->showMessage("Starting z-migrate process ...");
                system(command.toStdString().c_str());
            } else ui->statusBar->showMessage("Make sure you have zmigrate.exe and komodo-cli.exe binaries ...");
        } else ui->statusBar->showMessage("You should use sapling z-address starting with \"zs\" ...");
    } else ui->statusBar->showMessage("Coin and zaddress shouldn't be empty ...");
}
