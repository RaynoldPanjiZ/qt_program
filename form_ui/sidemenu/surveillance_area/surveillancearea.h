#ifndef SURVEILLANCEAREA_H
#define SURVEILLANCEAREA_H

#include <QWidget>

namespace Ui {
class SurveillanceArea;
}

class SurveillanceArea : public QWidget
{
    Q_OBJECT

public:
    explicit SurveillanceArea(QWidget *parent = nullptr);
    ~SurveillanceArea();

private:
    Ui::SurveillanceArea *ui;
};

#endif // SURVEILLANCEAREA_H
