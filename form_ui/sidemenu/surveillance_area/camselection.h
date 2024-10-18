#ifndef CAMSELECTION_H
#define CAMSELECTION_H

#include <QWidget>

namespace Ui {
class CamSelection;
}

class CamSelection : public QWidget
{
    Q_OBJECT

public:
    explicit CamSelection(QWidget *parent = nullptr);
    ~CamSelection();

private:
    Ui::CamSelection *ui;
};

#endif // CAMSELECTION_H
