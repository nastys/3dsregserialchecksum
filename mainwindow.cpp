#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inputfile = QFileDialog::getOpenFileName(this, "Open SecureInfo_A or SecureInfo_B", "", "SecureInfo (SecureInfo_A SecureInfo_B);;All files (*)");
    if(inputfile=="")
        return;

    QFile file(inputfile);
    file.open(QIODevice::ReadOnly);
    file.seek(256);
    QByteArray serial = file.read(18).toHex();
    ui->lineEdit_serial->setText(QString(serial));

    QString md5 = QString(QCryptographicHash::hash(serial, QCryptographicHash::Md5).toHex());
    ui->lineEdit_md5->setText(md5);
}
