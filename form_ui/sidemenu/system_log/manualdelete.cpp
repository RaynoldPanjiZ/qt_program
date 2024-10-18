#include "manualdelete.h"
#include "ui_manualdelete.h"

ManualDelete::ManualDelete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualDelete)
{
    ui->setupUi(this);
}

ManualDelete::~ManualDelete()
{
    delete ui;
}
