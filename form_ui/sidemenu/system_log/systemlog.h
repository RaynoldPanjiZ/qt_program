#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <QWidget>
#include "manualdelete.h"
#include "autodelete.h"
#include <QMainWindow>
#include <QDate>
#include <QTimer>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>
#include <QVBoxLayout>

namespace Ui {
class SystemLog;
}

class SystemLog : public QWidget
{
    Q_OBJECT

public:
    explicit SystemLog(QWidget *parent = nullptr);
    ~SystemLog();

private slots:
    void on_btn_manualDel_clicked();
    void on_btn_autoDel_clicked();

    void updateTable();

private:
    Ui::SystemLog *ui;
    ManualDelete *manual_delete;
    AutoDelete *auto_delete;

    QList<QJsonObject> datas;
    QTimer *timerFetch;

    void setupUI();
    void loadSystemLogData();
};

#endif // SYSTEMLOG_H
