#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
//#include <QProcess>
#include <QMessageBox>

#include <windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle(QString("ZMigrate Launcher"));
    ui->plainTextEdit->insertPlainText("put in your zs sapling address, make sure you have a backup of its z_exportkey\nstart and wait for it to complete, it will take approximately 1 minute per z-deposit you have");
    ui->plainTextEdit->viewport()->setAutoFillBackground(false);

    ui->linkLabel->setText("<a href=\"https://github.com/DeckerSU/komodo_dapps\">zmigrate (win)</a>");
    ui->linkLabel->setTextFormat(Qt::RichText);
    ui->linkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->linkLabel->setOpenExternalLinks(true);

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

    //QProcess process;

    bool komodocliExists = QFileInfo::exists(komodocli_binary) && QFileInfo(komodocli_binary).isFile();
    bool zmigrateExists = QFileInfo::exists(zmigrate_binary) && QFileInfo(zmigrate_binary).isFile();

    //qDebug() << "Coin: " + coin << "," << "ZAddress: " + zaddress;
    if (!(coin.isEmpty() || zaddress.isEmpty())) {
        if (zaddress.left(2) == QString("zs")) {
            if (komodocliExists && zmigrateExists)
            //if (true)
            {
                ui->statusBar->showMessage("Starting z-migrate process ...");
                //system(command.toStdString().c_str());

                /* we can't just start console process as QProcess::startDetached("cmd.exe");
                 * under windows, bcz if it started from GUI application it's window is hidden, bcz of
                 * https://codereview.qt-project.org/#/c/162585/7/src/corelib/io/qprocess_win.cpp
                 * and also we can't use system(command.toStdString().c_str()); bcz main window is hangs */

                bool success = false;
                PROCESS_INFORMATION pinfo;
                STARTUPINFOW startupInfo = { sizeof( STARTUPINFO ), 0, 0, 0,
                                             (ulong)CW_USEDEFAULT, (ulong)CW_USEDEFAULT,
                                             (ulong)CW_USEDEFAULT, (ulong)CW_USEDEFAULT,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                           };
                success = CreateProcess(0, (wchar_t*)command.utf16(),
                                        0, 0, FALSE, CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE, 0,
                                        0 /* workingdir */,
                                        &startupInfo, &pinfo);
                if (success) {
                    QMessageBox::information(this,"Information","Wait for zmigrate to complete, it will take approximately 1 minute per z-deposit you have ...");

                    /* put in your zs sapling address, make sure you have a backup of its z_exportkey
                       start and wait for it to complete, it will take approximately 1 minute per z-deposit you have */

                } else ui->statusBar->showMessage("Failed to start zmigrate ...");
            } else ui->statusBar->showMessage("Make sure you have zmigrate.exe and komodo-cli.exe binaries ...");
        } else ui->statusBar->showMessage("You should use sapling z-address starting with \"zs\" ...");
    } else ui->statusBar->showMessage("Coin and zaddress shouldn't be empty ...");
}
