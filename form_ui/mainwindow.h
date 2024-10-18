#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sidemenu/user_management/usrmgn.h"
#include "sidemenu/network_setting/netsetting.h"
#include "sidemenu/camera_map/cammap.h"
#include "sidemenu/custom_zone/customzone.h"
#include "sidemenu/surveillance_area/camselection.h"
#include "sidemenu/event_setting/eventsetting.h"
#include "sidemenu/aiengine_update/aiengineupdate.h"
#include "sidemenu/system_setting/systemsetting.h"
#include "sidemenu/system_log/systemlog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_user_management_clicked();

    void on_net_setting_clicked();

    void on_exit_btn_clicked();

    void on_camera_map_manag_clicked();

    void on_custom_zone_setting_clicked();

    void on_surv_area_setting_clicked();

    void on_event_setting_clicked();

    void on_ai_engine_up_clicked();

    void on_system_setting_clicked();

    void on_system_log_clicked();

private:
    Ui::MainWindow *ui;
    UsrMgn *usr_manag;
    NetSetting *net_setting;
    camMap *camera_map;
    CustomZone *zone_setting;
    CamSelection *camera_selection;
    EventSetting *event_setting;
    AIEngineUpdate *aiengine_update;
    SystemSetting *system_setting;
    SystemLog *system_log;
};

#endif // MAINWINDOW_H
