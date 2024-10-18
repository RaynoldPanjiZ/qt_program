#ifndef USRMGN_H
#define USRMGN_H

#include <QWidget>

namespace Ui {
class UsrMgn;
}

class UsrMgn : public QWidget
{
    Q_OBJECT

public:
    explicit UsrMgn(QWidget *parent = nullptr);
    ~UsrMgn();

private:
    Ui::UsrMgn *ui;
};

#endif // USRMGN_H
