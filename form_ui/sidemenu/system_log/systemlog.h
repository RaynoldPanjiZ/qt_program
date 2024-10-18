#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <QWidget>
#include "manualdelete.h"
#include "autodelete.h"

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

private:
    Ui::SystemLog *ui;
    ManualDelete *manual_delete;
    AutoDelete *auto_delete;
};

#endif // SYSTEMLOG_H
