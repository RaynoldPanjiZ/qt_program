#include "systemlog.h"
#include "ui_systemlog.h"

#include <cmath>

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

//    int positionStart = 0;
//    int positionEnd = dataToShow.size();
//    int numPerPage = dataToShow.size();
    auto [positionStart, positionEnd, numPerPage] = numPageFilter(dataToShow);

    tb_show->setRowCount(numPerPage);

    if (!dataToShow.isEmpty()) {
        for (int idx = positionStart; idx < positionEnd; ++idx) {
            if(idx==dataToShow.size()) break;
            qDebug() << "totalData:" << dataToShow.size();
            qDebug() << "get_idx:" << idx;
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


std::tuple<int, int, int> SystemLog::numPageFilter(const QList<QJsonObject> &dataToShow) {
    int numPerPage = ui->numDisplay_filter->currentText().toInt();
    int totalPage = std::ceil(static_cast<double>(dataToShow.size()) / numPerPage);
    qDebug() << "pages:" << totalPage;

    if (currPage > totalPage) {
        dataOperationPages(1);
    }

    QLayout *pgLayout = ui->pages_frame->layout();
    QLayoutItem *item;
    while ((item = pgLayout->takeAt(0)) != nullptr) {
        delete item->widget();
    }


    QSpacerItem *spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pgLayout->addItem(spacer1);

    QPushButton *prevBtn = new QPushButton("<<");
    prevBtn->setFixedSize(30, 30);
    connect(prevBtn, &QPushButton::clicked, [this]() { dataOperationPages(1); });
    pgLayout->addWidget(prevBtn);

    QList<QPushButton*> pageBtns;
    for (int i = 0; i < totalPage; ++i) {
        QPushButton *btn = new QPushButton(QString::number(i + 1));
        btn->setFixedSize(30, 30);
        connect(btn, &QPushButton::clicked, [this, i]() { dataOperationPages(i + 1); });
        pgLayout->addWidget(btn);
        pageBtns.append(btn);
    }

    QPushButton *nextBtn = new QPushButton(">>");
    nextBtn->setFixedSize(30, 30);
    connect(nextBtn, &QPushButton::clicked, [this, totalPage]() { dataOperationPages(totalPage); });
    pgLayout->addWidget(nextBtn);

    QSpacerItem *spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pgLayout->addItem(spacer2);


    qDebug() << "number page" << pageBtns.size();
    qDebug() << "current page" << currPage;

    if (!pageBtns.empty()){
        pageBtns[currPage-1]->setEnabled(false);
    }
    if (currPage == 1) {
        prevBtn->setEnabled(false);
    }
    if (currPage == totalPage || totalPage == 0){
        nextBtn->setEnabled(false);
    }

    int positionEnd = numPerPage * currPage;
    int positionStart = std::abs(positionEnd - numPerPage);

    if (dataToShow.size() <= 0){
        positionStart = 0;
        positionEnd = 0;
        return {positionStart, positionEnd, 0};
    }else if (dataToShow.size() < numPerPage){
        positionStart = 0;
        positionEnd = dataToShow.size();
        return {positionStart, positionEnd, positionEnd};
    }else if (dataToShow.size() < positionEnd){
        positionEnd = dataToShow.size();
        return {positionStart, positionEnd, positionEnd - positionStart};
    } else {
        return {positionStart, positionEnd, numPerPage};
    }
}

void SystemLog::dataOperationPages(int event) {
    currPage = event;
    updateTable();
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

