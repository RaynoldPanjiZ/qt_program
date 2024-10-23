#include "manualdelete.h"
#include "ui_manualdelete.h"
#include <QDate>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHeaderView>

ManualDelete::ManualDelete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualDelete)
{
    ui->setupUi(this);
    setWindowTitle("Manually Delete System Logs");

    connect(ui->btn_close, &QPushButton::clicked, this, &ManualDelete::close);

    // Set the current date in periodEnd_filter
    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    ui->periodEnd_filter->setDate(QDate::fromString(dateStr, "yyyy-MM-dd"));

    loadSystemLogData();

    // Initialize timer to refresh the table every 300ms
    timerFetch = new QTimer(this);
    connect(timerFetch, &QTimer::timeout, this, &ManualDelete::updateTable);
    timerFetch->start(300);
}

ManualDelete::~ManualDelete()
{
    delete ui;
}

void ManualDelete::loadSystemLogData() {
    QFile file("./datas/systemLog.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open systemLog.json file.");
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

void ManualDelete::updateTable(){
    QTableWidget *tb_show = ui->tb_show;

    QHeaderView *header = tb_show->horizontalHeader();
    header->setMinimumHeight(34);
//    header->setDefaultAlignment(Qt::AlignCenter | Qt::TextWordWrap);

    for (int i = 0; i < tb_show->columnCount(); ++i) {
        if (i == 0) {
            tb_show->setColumnWidth(i, 20);
        } else {
            header->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }

    QList<QJsonObject> dataToShow = datas;

    int positionStart = 0;
    int positionEnd = dataToShow.size();
    int numPerPage = dataToShow.size();

    tb_show->setRowCount(numPerPage);

    if (!dataToShow.isEmpty()) {
        for (int idx = positionStart; idx < positionEnd; ++idx) {
            const QJsonObject &data = dataToShow[idx];
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(idx + 1));
            item->setTextAlignment(Qt::AlignCenter);
            tb_show->setItem(idx - positionStart, 0, item);

            int col = 1;
            for (const QString &key : data.keys()) {
                if (key == "id") continue;
                QTableWidgetItem *item = new QTableWidgetItem(data[key].toString());
                item->setTextAlignment(Qt::AlignCenter);
                tb_show->setItem(idx - positionStart, col++, item);
            }
        }
    }
}
