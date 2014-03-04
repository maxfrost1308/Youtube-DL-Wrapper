#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class YoutubeDL;
}

class YoutubeDL : public QMainWindow
{
    Q_OBJECT

public:
    explicit YoutubeDL(QWidget *parent = 0);
    ~YoutubeDL();

private slots:
    void on_fetchButton_clicked();

    void on_downloadButton_clicked();

private:
    Ui::YoutubeDL *ui;
};

#endif // YoutubeDL_H
