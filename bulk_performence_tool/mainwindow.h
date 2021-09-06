#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "libusb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonStart_clicked();

    void bulk_out_transfer();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    uint16_t target_vid;
    uint16_t target_pid;
    libusb_device_handle *dev_handle;

    uint8_t pattern[1024];
    void setPattern();
};

#endif // MAINWINDOW_H
