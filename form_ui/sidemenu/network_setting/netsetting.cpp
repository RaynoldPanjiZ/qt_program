#include "netsetting.h"
#include "ui_netsetting.h"

NetSetting::NetSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetSetting)
{
    ui->setupUi(this);
}

NetSetting::~NetSetting()
{
    delete ui;
}
