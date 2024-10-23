#include "customzone.h"
#include "ui_customzone.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QHeaderView>
#include <QDebug>
#include <QCheckBox>

CustomZone::CustomZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomZone)
{
    ui->setupUi(this);

    setWindowTitle("User Defined Area Management");
    connect(ui->btn_close, &QPushButton::clicked, this, &CustomZone::close);

    loadUserDefinedData();
    setupZoneTable();
}

CustomZone::~CustomZone()
{
    delete ui;
}

void CustomZone::loadUserDefinedData() {
    QFile file("./datas/userDefined_data.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open user defined data file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
        datas.append(value.toObject());
    }
    file.close();
}

void CustomZone::setupZoneTable() {
    QTableWidget *tbZoneShow = ui->tbZone_show;
    tbZoneShow->setRowCount(datas.size());

    QHeaderView *header1 = tbZoneShow->horizontalHeader();
    for (int i = 0; i < tbZoneShow->columnCount(); ++i) {
        if (i == 0) {
            tbZoneShow->setColumnWidth(i, 20);
        } else {
            header1->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }

    for (int idx = 0; idx < datas.size(); ++idx) {
        const QJsonObject &data = datas[idx];

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(idx+1));
        item->setTextAlignment(Qt::AlignCenter);
        tbZoneShow->setItem(idx, 0, item);

        QTableWidgetItem *zoneNameItem = new QTableWidgetItem(data["zone_name"].toString());
        zoneNameItem->setTextAlignment(Qt::AlignCenter);
        tbZoneShow->setItem(idx, 1, zoneNameItem);
    }

    connect(tbZoneShow, &QTableWidget::cellClicked, this, &CustomZone::selectedRow);
}

void CustomZone::selectedRow(int row, int col) {
    ui->label_CamInfo->setText(datas[row]["zone_name"].toString());
    ui->zoneName_edit->setText(datas[row]["zone_name"].toString());

    setupCamTable(row);
}

void CustomZone::setupCamTable(int row_id) {
    const QJsonArray camInfos = datas[row_id]["cam_infos"].toArray();

    QTableWidget *tbCamShow = ui->tbCam_show;
    tbCamShow->setRowCount(camInfos.size());

    QHeaderView *header = tbCamShow->horizontalHeader();
    for (int i = 0; i < tbCamShow->columnCount(); ++i) {
        if (i == 0) {
            tbCamShow->setColumnWidth(i, 20);
        } else if (i == 3) {
            tbCamShow->setColumnWidth(i, 45);
        } else {
            header->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }

    for (int idx = 0; idx < camInfos.size(); ++idx) {
        const QJsonObject &camInfo = camInfos[idx].toObject();

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(idx+1));
        item->setTextAlignment(Qt::AlignCenter);
        tbCamShow->setItem(idx, 0, item);

        int col = 1;
        for (const QString &key : camInfo.keys()) {
            if (key == "status") {
                QFrame *chboxFrame = new QFrame();
                QHBoxLayout *chboxLayout = new QHBoxLayout(chboxFrame);
                QCheckBox *checkBox = new QCheckBox();
                checkBox->setChecked(camInfo[key].toInt() == 1);
                checkBox->setEnabled(false);
                chboxLayout->addWidget(checkBox);
                chboxLayout->setAlignment(checkBox, Qt::AlignCenter);
                chboxFrame->setLayout(chboxLayout);
                tbCamShow->setCellWidget(idx, col, chboxFrame);
            } else {
                QTableWidgetItem *valueItem = new QTableWidgetItem(camInfo[key].toString());
                valueItem->setTextAlignment(Qt::AlignCenter);
                tbCamShow->setItem(idx, col, valueItem);
            }
            col++;
        }
    }
}
