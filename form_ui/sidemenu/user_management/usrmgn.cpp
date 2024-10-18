#include "usrmgn.h"
#include "ui_usrmgn.h"

UsrMgn::UsrMgn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsrMgn)
{
    ui->setupUi(this);
}

UsrMgn::~UsrMgn()
{
    delete ui;
}
