#ifndef EVENTSETTING_H
#define EVENTSETTING_H

#include <QWidget>
#include "objrealtime.h"

namespace Ui {
class EventSetting;
}

class EventSetting : public QWidget
{
    Q_OBJECT

public:
    explicit EventSetting(QWidget *parent = nullptr);
    ~EventSetting();

private slots:
    void on_obj_track_btn_clicked();

private:
    Ui::EventSetting *ui;
    ObjRealtime *obj_realtime;
};

#endif // EVENTSETTING_H
