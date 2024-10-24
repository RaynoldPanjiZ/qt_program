#include "camselection.h"
#include "ui_camselection.h"
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QWidget>
#include <QtDebug>

CamSelection::CamSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamSelection)
{
    ui->setupUi(this);
    setWindowTitle("Camera Selection");

//    datas = {
//        {"192.168.100.101", "Korean Restaurant-1", "0", "rtsp://admin:aery2021!@192.168.45.166:554/cam/realmonitor?channel=1&subtype=0&unaicast=true&proto=Onvif"},
//        {"192.168.100.102", "Korean Restaurant-2", "1", "rtsp://admin:aery2021!@192.168.45.167:554/cam/realmonitor?channel=1&subtype=0&unaicast=true&proto=Onvif"}
//    };

    datas = {
        {"192.168.100.101", "Korean Restaurant-1", "0", "vid/test1.mp4"},
        {"192.168.100.102", "Korean Restaurant-2", "1", "vid/test2.mp4"}
    };

    QTableWidget *tb_show = ui->tb_show;
    tb_show->setRowCount(datas.size());

    QHeaderView *header = tb_show->horizontalHeader();
    header->setMinimumHeight(34);
    for (int i = 0; i < tb_show->columnCount(); ++i) {
        if (i == 0) {
            tb_show->setColumnWidth(i, 20);
        } else if (i == 3) {
            tb_show->setColumnWidth(i, 65);
//            header->setDefaultAlignment(Qt::AlignCenter | Qt::TextWordWrap);
        } else if (i == 4) {
            tb_show->setColumnWidth(i, 45);
        } else {
            header->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }

    // Isi data ke tabel
    for (int idx = 0; idx < datas.size(); ++idx) {
        QStringList data_if = datas[idx];
        QTableWidgetItem *it = new QTableWidgetItem(QString::number(idx + 1));  // numbering
        it->setTextAlignment(Qt::AlignCenter);
        tb_show->setItem(idx, 0, it);

        for (int i = 0; i < data_if.size(); ++i) {
            if (i == 2) {
                // Checkbox
                QCheckBox *checkbox = new QCheckBox(this);
                QFrame *chbox_frame = new QFrame();
                QHBoxLayout *chbox_layout = new QHBoxLayout(chbox_frame);
                checkbox->setChecked(data_if[i].toInt() == 1);
                checkbox->setEnabled(false);  // Disable checkbox
                chbox_layout->addWidget(checkbox);
                chbox_layout->setAlignment(checkbox, Qt::AlignCenter);
                chbox_frame->setLayout(chbox_layout);
                tb_show->setCellWidget(idx, i + 1, chbox_frame);
            } else if (i == 3) {
                // Radio button
                QRadioButton *radio_button = new QRadioButton();
                tb_show->setCellWidget(idx, i + 1, radio_button);
                connect(radio_button, &QRadioButton::clicked, [this, idx, radio_button]() {
                    selectedRow(idx, radio_button);
                });
            } else {
                QTableWidgetItem *it = new QTableWidgetItem(data_if[i]);
                it->setTextAlignment(Qt::AlignCenter);
                tb_show->setItem(idx, i + 1, it);
            }
        }
    }
}

CamSelection::~CamSelection()
{
    delete ui;
}


void CamSelection::selectedRow(int rowIdx, QRadioButton *radioWidget) {
    // Menggunakan OpenCV untuk menangkap stream video
    QString rtsp_url = datas[rowIdx][3];
    camera.open(rtsp_url.toStdString());

    if (!camera.isOpened()) {
        qDebug() << "Error opening video stream";
        return;
    }
    // Timer untuk memperbarui frame setiap 30ms
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CamSelection::displayVid);
    timer->start(30);

    qDebug() << rtsp_url;
}

void CamSelection::displayVid() {
    cv::Mat frame;
    if (camera.read(frame)) {
       cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

       QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
       QPixmap pixmap = QPixmap::fromImage(img);

       // Set pixmap to label_cam
       ui->label_cam->setPixmap(pixmap);
       ui->label_cam->setScaledContents(true);
    }
    qDebug() << "display";
}
