#include "systemlog.h"
#include "ui_systemlog.h"

SystemLog::SystemLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemLog)
{
    ui->setupUi(this);
}

SystemLog::~SystemLog()
{
    delete ui;
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

