#include "autodelete.h"
#include "ui_autodelete.h"

AutoDelete::AutoDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoDelete)
{
    ui->setupUi(this);
}

AutoDelete::~AutoDelete()
{
    delete ui;
}
