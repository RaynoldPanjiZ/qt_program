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

private slots:
    void selectedRow(int row, int col);

private:
    Ui::CustomZone *ui;

    QList<QJsonObject> datas;
    void loadUserDefinedData();
    void setupZoneTable();
    void setupCamTable(int row_id);
};

#endif // CUSTOMZONE_H
