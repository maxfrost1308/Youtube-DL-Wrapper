#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QProgressDialog>
#include <QRegularExpression>

YoutubeDL::YoutubeDL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YoutubeDL)
{
    ui->setupUi(this);
    setWindowTitle("YouTube-DL Wrapper");
    ui->statusBar->setSizeGripEnabled(false);
    ui->thumbLabel->setScaledContents(true);
}

YoutubeDL::~YoutubeDL()
{
    delete ui;
}

void YoutubeDL::on_fetchButton_clicked()
{
    QProcess p;
    QString pout, perr;
    p.start("youtube-dl --skip-download --write-thumbnail -o 1.jpg --get-title --get-description " + ui->urlBox->text());
    p.waitForFinished(-1);
    pout = p.readAllStandardOutput();
    perr = p.readAllStandardError();
    if (perr.length())
    {
        ui->descBox->setText("Error occured.\n" + perr);
        ui->thumbLabel->setEnabled(false);
        ui->descBox->setEnabled(false);
    }
    else
    {
        ui->descBox->setText(pout);
        ui->thumbLabel->setPixmap(QPixmap ("1.jpg"));
        ui->thumbLabel->setEnabled(true);
        ui->descBox->setEnabled(true);
    }
    p.start("youtube-dl -F " + ui->urlBox->text());
    p.waitForFinished(-1);
    pout = p.readAllStandardOutput();
    perr = p.readAllStandardError();
    ui->formatBox->clear();
    if (perr.length())
    {
        ui->formatBox->addItem("Error occured.");
        ui->formatBox->setEnabled(false);
        ui->downloadButton->setEnabled(false);
    }
    else
    {
        QStringList plist = pout.split('\n');
        foreach(QString line, plist)
            if (line!="Available formats:" && line[0]!='[' && line[0]!='\0')
                ui->formatBox->addItem(line);
        ui->formatBox->setEnabled(true);
        ui->downloadButton->setEnabled(true);
    }
}

void YoutubeDL::on_downloadButton_clicked()
{
    QString format = ui->formatBox->currentText(), get;
    int i=0;
    for (i=0; format[i]!='\t'; i++)
        get[i]=format[i];
    get[i]='\0';
    QProcess p;
    p.start("youtube-dl -f " + get + " " + ui->urlBox->text());
    /*ui->progressBar->setEnabled(true);
    while (!p.atEnd())
    {
        QString prog = p.readLine();
        QRegularExpression rx("[0-9]{1,3}\\.[0-9]{0,1}]");
        QRegularExpressionMatch m = rx.match(prog);
        if (m.hasMatch()) prog = m.captured(1);
        int perc = prog.toFloat();
        ui->progressBar->setValue(perc);
    }*/
    p.waitForFinished(-1);
    QString perr = p.readAllStandardError();
    if (perr.length())
        ui->descBox->setText("Error during download.\n" + perr);
    else
        ui->descBox->setText("Download completed!");
}
