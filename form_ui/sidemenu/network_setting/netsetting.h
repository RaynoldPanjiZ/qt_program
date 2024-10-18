#ifndef NETSETTING_H
#define NETSETTING_H

#include <QWidget>

namespace Ui {
class NetSetting;
}

class NetSetting : public QWidget
{
    Q_OBJECT

public:
    explicit NetSetting(QWidget *parent = nullptr);
    ~NetSetting();

private:
    Ui::NetSetting *ui;
};

#endif // NETSETTING_H
