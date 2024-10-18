#include "eventsetting.h"
#include "ui_eventsetting.h"

EventSetting::EventSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventSetting)
{
    ui->setupUi(this);
}

EventSetting::~EventSetting()
{
    delete ui;
}

void EventSetting::on_obj_track_btn_clicked()
{
    obj_realtime = new ObjRealtime(0);
    obj_realtime->show();
}

