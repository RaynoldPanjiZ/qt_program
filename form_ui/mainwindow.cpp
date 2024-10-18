#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::cout << "Test AIBOX";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_net_setting_clicked()
{
    net_setting = new NetSetting(0);
    net_setting->show();
}

void MainWindow::on_user_management_clicked()
{
    usr_manag = new UsrMgn(0);
    usr_manag->show();
}

void MainWindow::on_camera_map_manag_clicked()
{
    camera_map = new camMap(0);
    camera_map->show();
}

void MainWindow::on_custom_zone_setting_clicked()
{
    zone_setting = new CustomZone(0);
    zone_setting->show();
}

void MainWindow::on_surv_area_setting_clicked()
{
    camera_selection = new CamSelection(0);
    camera_selection->show();
}

void MainWindow::on_event_setting_clicked()
{
    event_setting = new EventSetting(0);
    event_setting->show();
}

void MainWindow::on_ai_engine_up_clicked()
{
    aiengine_update = new AIEngineUpdate(0);
    aiengine_update->show();
}

void MainWindow::on_system_setting_clicked()
{
    system_setting = new SystemSetting(0);
    system_setting->show();
}

void MainWindow::on_system_log_clicked()
{
    system_log = new SystemLog(0);
    system_log->show();
}





void MainWindow::on_exit_btn_clicked()
{
    this->close();
}

