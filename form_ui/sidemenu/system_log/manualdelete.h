#ifndef MANUALDELETE_H
#define MANUALDELETE_H

#include <QWidget>
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
class ManualDelete;
}

class ManualDelete : public QWidget
{
    Q_OBJECT

public:
    explicit ManualDelete(QWidget *parent = nullptr);
    ~ManualDelete();

private slots:
    void updateTable();

private:
    Ui::ManualDelete *ui;

    QList<QJsonObject> datas;
    QTimer *timerFetch;

    void loadSystemLogData();
};

#endif // MANUALDELETE_H
