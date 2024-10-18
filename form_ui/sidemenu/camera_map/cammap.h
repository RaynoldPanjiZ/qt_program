#ifndef CAMMAP_H
#define CAMMAP_H

#include <QWidget>

namespace Ui {
class camMap;
}

class camMap : public QWidget
{
    Q_OBJECT

public:
    explicit camMap(QWidget *parent = nullptr);
    ~camMap();

private:
    Ui::camMap *ui;
};

#endif // CAMMAP_H
