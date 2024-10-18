#include "objrealtime.h"
#include "ui_objrealtime.h"

ObjRealtime::ObjRealtime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjRealtime)
{
    ui->setupUi(this);
}

ObjRealtime::~ObjRealtime()
{
    delete ui;
}
