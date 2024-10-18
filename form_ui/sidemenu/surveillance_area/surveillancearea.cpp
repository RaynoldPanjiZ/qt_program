#include "surveillancearea.h"
#include "ui_surveillancearea.h"

SurveillanceArea::SurveillanceArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SurveillanceArea)
{
    ui->setupUi(this);
}

SurveillanceArea::~SurveillanceArea()
{
    delete ui;
}
