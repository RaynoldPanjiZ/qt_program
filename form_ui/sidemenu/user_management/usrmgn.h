#ifndef USRMGN_H
#define USRMGN_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QComboBox>
#include <QTableWidget>

namespace Ui {
class UsrMgn;
}

class UsrMgn : public QWidget
{
    Q_OBJECT

public:
    explicit UsrMgn(QWidget *parent = nullptr);
    ~UsrMgn();

private slots:
    void updateTable();
    void selectedRow(int row_id, int col_id);
    void changePassword();
    void deleteRow(int row_id);

private:
    Ui::UsrMgn *ui;
    QDialog *dialog;

    QList<QJsonObject> datas;
    QStringList grouplist;
    QTimer *timerFetch;

    void loadUserData();
};

#endif // USRMGN_H
