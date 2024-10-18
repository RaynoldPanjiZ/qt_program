#ifndef MANUALDELETE_H
#define MANUALDELETE_H

#include <QWidget>

namespace Ui {
class ManualDelete;
}

class ManualDelete : public QWidget
{
    Q_OBJECT

public:
    explicit ManualDelete(QWidget *parent = nullptr);
    ~ManualDelete();

private:
    Ui::ManualDelete *ui;
};

#endif // MANUALDELETE_H
