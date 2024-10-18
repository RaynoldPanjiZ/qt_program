#ifndef AUTODELETE_H
#define AUTODELETE_H

#include <QDialog>

namespace Ui {
class AutoDelete;
}

class AutoDelete : public QDialog
{
    Q_OBJECT

public:
    explicit AutoDelete(QWidget *parent = nullptr);
    ~AutoDelete();

private:
    Ui::AutoDelete *ui;
};

#endif // AUTODELETE_H
