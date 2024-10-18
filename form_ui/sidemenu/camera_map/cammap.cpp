#include "cammap.h"
#include "ui_cammap.h"

camMap::camMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camMap)
{
    ui->setupUi(this);
}

camMap::~camMap()
{
    delete ui;
}
