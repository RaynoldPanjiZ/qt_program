QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += link_pkgconfig
#PKGCONFIG += opencv4


TARGET = AIbox_GUI
TEMPLATE = app

DEFINES += Q_COMPILER_INITIALIZER_LISTS

SOURCES += main.cpp \
    form_ui/mainwindow.cpp \
    form_ui/sidemenu/aiengine_update/aiengineupdate.cpp \
    form_ui/sidemenu/camera_map/cammap.cpp \
    form_ui/sidemenu/custom_zone/customzone.cpp \
    form_ui/sidemenu/event_setting/eventsetting.cpp \
    form_ui/sidemenu/event_setting/objrealtime.cpp \
    form_ui/sidemenu/network_setting/netsetting.cpp \
    form_ui/sidemenu/surveillance_area/camselection.cpp \
    form_ui/sidemenu/surveillance_area/surveillancearea.cpp \
    form_ui/sidemenu/system_log/autodelete.cpp \
    form_ui/sidemenu/system_log/manualdelete.cpp \
    form_ui/sidemenu/system_log/systemlog.cpp \
    form_ui/sidemenu/system_setting/systemsetting.cpp \
    form_ui/sidemenu/user_management/usrmgn.cpp

HEADERS += \
    form_ui/mainwindow.h \
    form_ui/sidemenu/aiengine_update/aiengineupdate.h \
    form_ui/sidemenu/camera_map/cammap.h \
    form_ui/sidemenu/custom_zone/customzone.h \
    form_ui/sidemenu/event_setting/eventsetting.h \
    form_ui/sidemenu/event_setting/objrealtime.h \
    form_ui/sidemenu/network_setting/netsetting.h \
    form_ui/sidemenu/surveillance_area/camselection.h \
    form_ui/sidemenu/surveillance_area/surveillancearea.h \
    form_ui/sidemenu/system_log/autodelete.h \
    form_ui/sidemenu/system_log/manualdelete.h \
    form_ui/sidemenu/system_log/systemlog.h \
    form_ui/sidemenu/system_setting/systemsetting.h \
    form_ui/sidemenu/user_management/usrmgn.h

FORMS += \
    form_ui/mainwindow.ui \
    form_ui/sidemenu/aiengine_update/aiengineupdate.ui \
    form_ui/sidemenu/camera_map/cammap.ui \
    form_ui/sidemenu/custom_zone/customzone.ui \
    form_ui/sidemenu/event_setting/eventsetting.ui \
    form_ui/sidemenu/event_setting/objrealtime.ui \
    form_ui/sidemenu/event_setting/selectdata.ui \
    form_ui/sidemenu/network_setting/netsetting.ui \
    form_ui/sidemenu/surveillance_area/camselection.ui \
    form_ui/sidemenu/surveillance_area/surveillancearea.ui \
    form_ui/sidemenu/system_log/autodelete.ui \
    form_ui/sidemenu/system_log/manualdelete.ui \
    form_ui/sidemenu/system_log/systemlog.ui \
    form_ui/sidemenu/system_setting/systemsetting.ui \
    form_ui/sidemenu/user_management/changepass.ui \
    form_ui/sidemenu/user_management/usrmgn.ui

RESOURCES += \
    resource.qrc
