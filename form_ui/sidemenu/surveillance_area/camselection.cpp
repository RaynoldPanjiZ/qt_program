#include "camselection.h"
#include "ui_camselection.h"

CamSelection::CamSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamSelection)
{
    ui->setupUi(this);
}

CamSelection::~CamSelection()
{
    delete ui;
}
