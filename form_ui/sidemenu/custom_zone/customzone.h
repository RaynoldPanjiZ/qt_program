#ifndef CUSTOMZONE_H
#define CUSTOMZONE_H

#include <QWidget>

namespace Ui {
class CustomZone;
}

class CustomZone : public QWidget
{
    Q_OBJECT

public:
    explicit CustomZone(QWidget *parent = nullptr);
    ~CustomZone();

private:
    Ui::CustomZone *ui;
};

#endif // CUSTOMZONE_H
