#ifndef OBJREALTIME_H
#define OBJREALTIME_H

#include <QWidget>
#include <QJsonArray>
#include <QTableWidget>

namespace Ui {
class ObjRealtime;
}

class ObjRealtime : public QWidget
{
    Q_OBJECT

public:
    explicit ObjRealtime(QWidget *parent = nullptr);
    ~ObjRealtime();

private slots:
    void select_form();
    void selected_row(int row_id, int col_id);
    void resetInput();
    void handleFilter();
    void show_filter();

private:
    Ui::ObjRealtime *ui;
    QDialog *dialog;

    QList<QJsonObject> filtered_datas; // filtered all datas
    QJsonArray datas1;  // Data for persons
    QJsonArray datas2;  // Data for vehicles
    QString form;       // To track current form type (person or vehicle)
};

#endif // OBJREALTIME_H
