#include "systemlog.h"
#include "ui_systemlog.h"

SystemLog::SystemLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemLog)
{
    ui->setupUi(this);
    setWindowTitle("System Settings");

    connect(ui->btn_close, &QPushButton::clicked, this, &SystemLog::close);

    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    QDate qDate = QDate::fromString(dateStr, "yyyy-MM-dd");
    ui->periodEnd_filter->setDate(qDate);

    loadSystemLogData();

    timerFetch = new QTimer(this);
    connect(timerFetch, &QTimer::timeout, this, &SystemLog::updateTable);
    timerFetch->start(700);
}

SystemLog::~SystemLog()
{
    delete ui;
}


void SystemLog::loadSystemLogData() {
    QFile file("./datas/systemLog.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open system log file.");
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


void SystemLog::updateTable(){
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






void SystemLog::on_btn_manualDel_clicked()
{
    manual_delete = new ManualDelete(0);
    manual_delete->show();
}


void SystemLog::on_btn_autoDel_clicked()
{
    auto_delete = new AutoDelete(0);
    auto_delete->exec();
}

