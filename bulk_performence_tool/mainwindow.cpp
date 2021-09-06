#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    libusb_init(nullptr);

    this->dev_handle = nullptr;
    this->target_vid = 0x0416;
    this->target_pid = 0xC144;

    this->setPattern();

    ui->labelStatus->setText("");

    ui->lineEditInterval->setValidator(new QIntValidator(0, 100, this));
    ui->lineEditInterval->setText("30");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPattern()
{
    uint32_t tmp = 0, i;

    for (i = 0; i < 1024; i++) {
        this->pattern[i] = (uint8_t)tmp;
        if (tmp++ > 0xFF)
            tmp = 0;
    }
}

void MainWindow::bulk_out_transfer()
{
    int res, outed;

    if (this->dev_handle != nullptr) {
        // Host -> device
        res = libusb_interrupt_transfer(dev_handle, 3, pattern, 64, &outed, 0);
        if (res < 0) {
            qDebug("bulk transfer error, %d\n", res);
        }
        qDebug("Done, out <%d>\n", outed);
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    int res;

    if (this->dev_handle == nullptr) {

        qDebug("Opening device %04X:%04X...\n", this->target_vid, this->target_pid);
        dev_handle = libusb_open_device_with_vid_pid(nullptr, this->target_vid, target_pid);
        if (dev_handle == nullptr) {
            qDebug("Open device failed.\n");
            ui->labelStatus->setText("Fail");
            return;
        }

        res = libusb_kernel_driver_active(dev_handle, 0);
        if (res == 1) {
            libusb_detach_kernel_driver(dev_handle, 0);
            qDebug("driver error\n");
            ui->labelStatus->setText("Fail");
            return;
        }

        res = libusb_claim_interface(dev_handle, 0);
        if (res < 0) {
            qDebug("claim interface error:%d\n", res);
            ui->labelStatus->setText("Fail");
            return;
        }

        ui->labelStatus->setText("Connected");
    }
}

void MainWindow::on_pushButtonStart_clicked()
{
    this->bulk_out_transfer();

}
