#include "aiengineupdate.h"
#include "ui_aiengineupdate.h"

AIEngineUpdate::AIEngineUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AIEngineUpdate)
{
    ui->setupUi(this);
}

AIEngineUpdate::~AIEngineUpdate()
{
    delete ui;
}
