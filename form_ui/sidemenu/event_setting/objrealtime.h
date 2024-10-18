#ifndef OBJREALTIME_H
#define OBJREALTIME_H

#include <QWidget>

namespace Ui {
class ObjRealtime;
}

class ObjRealtime : public QWidget
{
    Q_OBJECT

public:
    explicit ObjRealtime(QWidget *parent = nullptr);
    ~ObjRealtime();

private:
    Ui::ObjRealtime *ui;
};

#endif // OBJREALTIME_H
