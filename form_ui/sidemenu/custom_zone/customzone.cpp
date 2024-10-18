#include "customzone.h"
#include "ui_customzone.h"

CustomZone::CustomZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomZone)
{
    ui->setupUi(this);
}

CustomZone::~CustomZone()
{
    delete ui;
}
