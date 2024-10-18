#ifndef AIENGINEUPDATE_H
#define AIENGINEUPDATE_H

#include <QWidget>

namespace Ui {
class AIEngineUpdate;
}

class AIEngineUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit AIEngineUpdate(QWidget *parent = nullptr);
    ~AIEngineUpdate();

private:
    Ui::AIEngineUpdate *ui;
};

#endif // AIENGINEUPDATE_H
