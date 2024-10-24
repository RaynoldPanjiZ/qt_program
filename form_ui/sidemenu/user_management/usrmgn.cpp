#include "usrmgn.h"
#include "ui_usrmgn.h"
#include "ui_changepass.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QHeaderView>
#include <QMessageBox>

UsrMgn::UsrMgn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsrMgn)
{
    ui->setupUi(this);
    setWindowTitle("User Management");

    // Initialize group list
    grouplist << "system administrator" << "manager" << "regular user";
    ui->usrGroup_comboBox->addItems(grouplist);

    // Connect buttons
    connect(ui->chpasswd_btn, &QPushButton::clicked, this, &UsrMgn::changePassword);
    connect(ui->close_btn, &QPushButton::clicked, this, &UsrMgn::close);

    // Load user data
    loadUserData();

    // Timer to update table
    timerFetch = new QTimer(this);
    connect(timerFetch, &QTimer::timeout, this, &UsrMgn::updateTable);
    timerFetch->start(700);
}

UsrMgn::~UsrMgn()
{
    delete ui;
}


void UsrMgn::loadUserData() {
    QFile file("./datas/userManagement.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open userManagement.json file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
        datas.append(value.toObject());
    }

    file.close();
}

void UsrMgn::updateTable() {
    QTableWidget *tbShow = ui->tb_show;
    tbShow->setRowCount(datas.size());

    QHeaderView *header = tbShow->horizontalHeader();
    for (int i = 0; i < tbShow->columnCount(); ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int idx = 0; idx < datas.size(); ++idx) {
        const QJsonObject &data = datas[idx];

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(idx + 1));
        item->setTextAlignment(Qt::AlignCenter);
        tbShow->setItem(idx, 0, item);

        int col = 0;
        for (const QString &key : data.keys()) {
            if (key == "password") continue;

            if (key == "msg" || key == "img") {
                QCheckBox *checkbox = new QCheckBox();
                checkbox->setChecked(data[key].toInt() == 1);
                checkbox->setEnabled(false);
                if (key == "msg"){
                    col = 6;
                } else if (key == "img"){
                    col = 7;
                }
                tbShow->setCellWidget(idx, col, checkbox);
            } else {
                if (key == "id"){
                    col = 1;
                } else if (key == "name"){
                    col = 2;
                } else if (key == "usr_group"){
                    col = 3;
                } else if (key == "contact"){
                    col = 4;
                } else if (key == "email"){
                    col = 5;
                }
                QTableWidgetItem *valueItem = new QTableWidgetItem(data[key].toString());
                valueItem->setTextAlignment(Qt::AlignCenter);
                tbShow->setItem(idx, col, valueItem);
            }
        }

        QPushButton *btnDelete = new QPushButton("Delete");
        tbShow->setCellWidget(idx, 8, btnDelete);
        connect(btnDelete, &QPushButton::clicked, [=]() { deleteRow(idx); });
        connect(tbShow, &QTableWidget::cellClicked, this, &UsrMgn::selectedRow);
    }
}


void UsrMgn::selectedRow(int row_id, int /*col_id*/) {
    const QJsonObject &data = datas[row_id];
    ui->id_edit->setText(data["id"].toString());
    ui->name_edit->setText(data["name"].toString());
    ui->contact_edit->setText(data["contact"].toString());
    ui->email_edit->setText(data["email"].toString());
    ui->pass_edit->setText(data["password"].toString());
    ui->verifyPass_edit->setText(data["password"].toString());

    for (int i = 0; i < grouplist.size(); ++i) {
        if (data["usr_group"].toString() == grouplist[i]) {
            ui->usrGroup_comboBox->setCurrentIndex(i);
            break;
        }
    }

    ui->msg_checkbox->setChecked(data["msg"].toInt() == 1);
    ui->img_checkBox->setChecked(data["img"].toInt() == 1);
}


void UsrMgn::deleteRow(int row_id) {
    selectedRow(row_id, false);
    QString id = datas[row_id]["id"].toString();
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete User",
        QString("Do you want to delete user ID '%1'?").arg(id),
        QMessageBox::Cancel | QMessageBox::Yes);
//    if (reply == QMessageBox::Yes) {
//        datas.removeAt(row_id);
//        updateTable();
//        QFile file("./datas/userManagement.json");
//        if (file.open(QIODevice::WriteOnly)) {
//            QJsonDocument doc(QJsonArray::fromVariantList(datas));
//            file.write(doc.toJson(QJsonDocument::Indented));
//            file.close();
//        }
//    }
}

void UsrMgn::changePassword(){
    /*** load selectdata.ui ***/
    dialog = new QDialog(this);
    Ui::ChangePass dialogUi;
    dialogUi.setupUi(dialog);
    connect(dialogUi.btn_cancel, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
