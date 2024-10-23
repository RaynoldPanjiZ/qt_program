#include "objrealtime.h"
#include "ui_objrealtime.h"
#include "ui_selectdata.h"
#include <QDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QWidget>

ObjRealtime::ObjRealtime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjRealtime)
{
    ui->setupUi(this);

    QString jsonFilePath = "./datas/objTracking.json";
    if (QFile::exists(jsonFilePath)) {
        QFile loadFile(QStringLiteral("./datas/objTracking.json"));
        if (loadFile.open(QIODevice::ReadOnly)) {
            QByteArray saveData = loadFile.readAll();
            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
            QJsonObject jsonObject = loadDoc.object();
            datas1 = jsonObject["person"].toArray();
            datas2 = jsonObject["vehicle"].toArray();
        }
        qDebug() << "Person datas:" << datas1.size();
        qDebug() << "Vehicle datas:" << datas2.size();
    } else {
        qDebug() << "JSON file does not exist. Creating a new one...";

        QJsonObject jsonObj;
        jsonObj["camera"] = QJsonObject(); // camera is an empty object
        jsonObj["person"] = QJsonArray(); // person is an empty array
        jsonObj["vehicle"] = QJsonArray(); // vehicle is an empty array

        QJsonDocument jsonDoc(jsonObj);
        QFile file(jsonFilePath);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "Cannot open JSON file for writing!";
            return;
        }
        file.write(jsonDoc.toJson());
        file.close();

        qDebug() << "New JSON file created with default values.";
    }

    connect(ui->person_select_btn, &QPushButton::clicked, this, &ObjRealtime::select_form);     // if select button in person clicked
    connect(ui->vehicle_select_btn, &QPushButton::clicked, this, &ObjRealtime::select_form);     // if select button in vehicle clicked
    connect(ui->reset_btn, &QPushButton::clicked, this, &ObjRealtime::resetInput);

    connect(ui->startSearch_btn, &QPushButton::clicked, this, &ObjRealtime::handleFilter);
    connect(ui->searchResult_btn, &QPushButton::clicked, this, &ObjRealtime::show_filter);

    connect(ui->close_btn, &QPushButton::clicked, this, &ObjRealtime::close);
}

ObjRealtime::~ObjRealtime()
{
    delete ui;
}

void ObjRealtime::select_form(){
    /*** load selectdata.ui ***/
    dialog = new QDialog(this);
    Ui::SelectData dialogUi;
    dialogUi.setupUi(dialog);
    connect(dialogUi.cancel_btn, &QPushButton::clicked, dialog, &QDialog::reject);


    QTableWidget *tb_show = dialogUi.tb_show;
    QStringList headerItems;
    QJsonArray data_to_show;

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button == ui->person_select_btn) {
        dialogUi.label_head1->setText("Data Person");
        headerItems << "No." << "Name" << "Img" << "Gender" << "Hairstyle" << "Attributes" << "Vehicle";
        data_to_show = datas1;
        form = "Person";

    } else if (button == ui->vehicle_select_btn) {
        dialogUi.label_head1->setText("Data Vehicle");
        headerItems << "No." << "Vehicle No" << "Car Type" << "Brand" << "Model" << "Color" << "Person";
        data_to_show = datas2;
        form = "Vehicle";
    }

    // Set header for table
    tb_show->setRowCount(data_to_show.size());
    tb_show->setColumnCount(headerItems.size());
    tb_show->setHorizontalHeaderLabels(headerItems);

    // Set table properties
    QHeaderView *header = tb_show->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    tb_show->setColumnWidth(0, 30);  // Resize the first column for "No."

    // Populate the table with data
    for (int row = 0; row < data_to_show.size(); ++row) {
        QJsonObject obj = data_to_show[row].toObject();

        QTableWidgetItem *itemNo = new QTableWidgetItem(QString::number(row + 1));
        tb_show->setItem(row, 0, itemNo);

        if (form == "Person") {
            tb_show->setItem(row, 1, new QTableWidgetItem(obj["name"].toString()));
            tb_show->setItem(row, 2, new QTableWidgetItem(obj["img"].toString()));
            tb_show->setItem(row, 3, new QTableWidgetItem(obj["gender"].toString()));
            tb_show->setItem(row, 4, new QTableWidgetItem(obj["hairstyle"].toString()));
            QStringList attrList;
            for (const QJsonValue &attr : obj["attribute"].toArray()) {
                attrList << attr.toString();
            }
            QString attributesStr = attrList.join(", ");
            tb_show->setItem(row, 5, new QTableWidgetItem(attributesStr));

            QString vehiclesStr;
            if(obj["vehicles"].toArray().empty()){
                vehiclesStr = "None";
            } else if (obj["vehicles"].toArray().size() >= 0) {
                QStringList vehicleList;
                for (const QJsonValue &attr : obj["vehicles"].toArray()) {
                    vehicleList << attr.toString();
                }
                vehiclesStr = vehicleList.join(", ");
            } else {
                vehiclesStr = obj["vehicles"].toArray()[0].toString();
            }
            tb_show->setItem(row, 6, new QTableWidgetItem(vehiclesStr));

        } else if (form == "Vehicle") {
            tb_show->setItem(row, 1, new QTableWidgetItem(obj["vehicle_no"].toString()));
            tb_show->setItem(row, 2, new QTableWidgetItem(obj["type"].toString()));
            tb_show->setItem(row, 3, new QTableWidgetItem(obj["brand"].toString()));
            tb_show->setItem(row, 4, new QTableWidgetItem(obj["model"].toString()));
            tb_show->setItem(row, 5, new QTableWidgetItem(obj["color"].toString()));

            QJsonValue personId = obj["person_id"];
            int Id_int = personId.toInt();
            if (personId.isBool() && personId.toBool() == false){
                tb_show->setItem(row, 6, new QTableWidgetItem("None"));
            } else if (Id_int >= 0) {
//                qDebug() << "\n AA" << personId << "\n\n";
                tb_show->setItem(row, 6, new QTableWidgetItem(datas1[Id_int].toObject()["name"].toString()));
            }
        }
        connect(tb_show, &QTableWidget::cellClicked, this, &ObjRealtime::selected_row);
    }

    dialog->exec();
}


void ObjRealtime::selected_row(int row_id, int col_id)
{
    dialog->close();
    if (form == "Person") {
        QJsonObject datatoform = datas1[row_id].toObject();

        QString name = datatoform["name"].toString();
        ui->personName->setText(name);

        QString profile_file = datatoform["img"].toString();
        QPixmap pixmap(profile_file);
        QPixmap scaledPixmap = pixmap.scaled(ui->label_foto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_foto->setPixmap(scaledPixmap);

        QString gender = datatoform["gender"].toString();
        if (ui->Gmale_radiobtn->text() == gender) {
            ui->Gmale_radiobtn->setChecked(true);
        } else if (ui->Gfemale_radiobtn->text() == gender) {
            ui->Gfemale_radiobtn->setChecked(true);
        }

        QString hair = datatoform["hairstyle"].toString();
        if (ui->Hlong_radiobtn->text() == hair) {
            ui->Hlong_radiobtn->setChecked(true);
        } else if (ui->Hshort_radiobtn->text() == hair) {
            ui->Hshort_radiobtn->setChecked(true);
        }

        QJsonArray attributes = datatoform["attribute"].toArray();
        QCheckBox *hat_chk = ui->attrHat_chbx;
        QCheckBox *bag_chk = ui->attrBag_chbx;
        QCheckBox *mask_chk = ui->attrMask_chbx;
        QCheckBox *glasses_chk = ui->attrGlasses_chbx;
        hat_chk->setChecked(false);
        bag_chk->setChecked(false);
        mask_chk->setChecked(false);
        glasses_chk->setChecked(false);
        for (const QJsonValue &value : attributes) {
            if (value.toString() == hat_chk->text()) {
                hat_chk->setChecked(true);
            } else if (value.toString() == bag_chk->text()) {
                bag_chk->setChecked(true);
            } else if (value.toString() == mask_chk->text()) {
                mask_chk->setChecked(true);
            } else if (value.toString() == glasses_chk->text()) {
                glasses_chk->setChecked(true);
            }
        }

    } else if (form == "Vehicle") {
        QJsonObject datatoform = datas2[row_id].toObject();

        ui->noVehicle->setText(datatoform["vehicle_no"].toString());
        ui->car_comboBox->setCurrentText(datatoform["type"].toString());
        ui->brand_comboBox->setCurrentText(datatoform["brand"].toString());
        ui->model_comboBox->setCurrentText(datatoform["model"].toString());
        ui->color_comboBox->setCurrentText(datatoform["color"].toString());
    }
}


void ObjRealtime::resetInput() {
    // Reset person name
    ui->personName->clear();

    // Reset vehicle no
    ui->noVehicle->clear();

    // Reset gender radio buttons
    ui->genderbtngroup->setExclusive(false);
    ui->Gmale_radiobtn->setChecked(false);
    ui->Gfemale_radiobtn->setChecked(false);
    ui->genderbtngroup->setExclusive(true);

    // Reset hairstyle radio buttons
    ui->hairbtngroup->setExclusive(false);
    ui->Hlong_radiobtn->setChecked(false);
    ui->Hshort_radiobtn->setChecked(false);
    ui->hairbtngroup->setExclusive(true);

    // Reset attributes checkboxes
    ui->attrHat_chbx->setChecked(false);
    ui->attrBag_chbx->setChecked(false);
    ui->attrMask_chbx->setChecked(false);
    ui->attrGlasses_chbx->setChecked(false);

    // Reset combo boxes
    ui->car_comboBox->setCurrentIndex(-1);
    ui->brand_comboBox->setCurrentIndex(-1);
    ui->model_comboBox->setCurrentIndex(-1);
    ui->color_comboBox->setCurrentIndex(-1);
}



void ObjRealtime::handleFilter() {
    QString nameFilter = ui->personName->text();
    QString genderFilter = ui->Gmale_radiobtn->isChecked() ? "Male" :
                           (ui->Gfemale_radiobtn->isChecked() ? "Female" : QString());
    QString hairstyleFilter = ui->Hlong_radiobtn->isChecked() ? "Long" :
                              (ui->Hshort_radiobtn->isChecked() ? "Short" : QString());
    QStringList attrsFilter;
    QList<QCheckBox*> checkboxes = ui->attr_checkboxGroup->findChildren<QCheckBox*>();
    for (QCheckBox *chbx : checkboxes) {
        if (chbx->isChecked()) {
            attrsFilter.append(chbx->text());
        }
    }

    QString vehicleFilter = ui->noVehicle->text();
    QString typeFilter = ui->car_comboBox->currentText();
    QString brandFilter = ui->brand_comboBox->currentText();
    QString modelFilter = ui->model_comboBox->currentText();
    QString colorFilter = ui->color_comboBox->currentText();

    bool nameIsSet = !nameFilter.isEmpty();
    bool genderIsSet = !genderFilter.isEmpty();
    bool hairIsSet = !hairstyleFilter.isEmpty();
    bool attrIsSet = !attrsFilter.isEmpty();

    bool vehicleIsSet = !vehicleFilter.isEmpty();
    bool typeIsSet = !typeFilter.isEmpty();
    bool brandIsSet = !brandFilter.isEmpty();
    bool modelIsSet = !modelFilter.isEmpty();
    bool colorIsSet = !colorFilter.isEmpty();

    filtered_datas.clear();
    QJsonArray filtered1;
    QJsonArray filtered2;

    // Filter data in datas1
    if (nameIsSet || genderIsSet || hairIsSet || attrIsSet) {
        for (const QJsonValue &value : datas1) {
            QJsonObject d1 = value.toObject();
            bool nameMatch = nameFilter.isEmpty() || (d1["name"].toString() == nameFilter);
            bool genderMatch = genderFilter.isEmpty() || (d1["gender"].toString() == genderFilter);
            bool hairMatch = hairIsSet ? (d1["hairstyle"].toString() == hairstyleFilter) : true;

            // Assuming "attribute" is a JSON array in the person object
            QJsonArray attributes = d1["attribute"].toArray();
            bool attrsMatch = attrsFilter.isEmpty() || std::all_of(attrsFilter.begin(), attrsFilter.end(),
                [&attributes](const QString& attr) {
                    return std::find_if(attributes.begin(), attributes.end(),
                                       [&attr](const QJsonValue &val) {
                                           return val.toString() == attr;
                                       }) != attributes.end();
                });

            if (nameMatch && genderMatch && hairMatch && attrsMatch) {
                filtered1.append(d1);
            }
        }
    }

    // Filter data in datas2
    if (vehicleIsSet || typeIsSet || brandIsSet || modelIsSet || colorIsSet) {
        for (const QJsonValue &value : datas2) {
            QJsonObject d2 = value.toObject();
            bool vehicleMatch = vehicleFilter.isEmpty() || (d2["vehicle_no"].toString() == vehicleFilter);
            bool typeMatch = typeIsSet ? (d2["type"].toString() == typeFilter) : true;
            bool brandMatch = brandIsSet ? (d2["brand"].toString() == brandFilter) : true;
            bool modelMatch = modelIsSet ? (d2["model"].toString() == modelFilter) : true;
            bool colorMatch = colorIsSet ? (d2["color"].toString() == colorFilter) : true;

            if (vehicleMatch && typeMatch && brandMatch && modelMatch && colorMatch) {
                filtered2.append(d2);
            }
        }
    }

    // Combine results from filtered1 and filtered2 based on relations
    if (!filtered1.isEmpty() && !filtered2.isEmpty()) {
        for (const QJsonValue &fil1Val : filtered1) {
            QJsonObject fil1 = fil1Val.toObject();
            for (const QJsonValue &fil2Val : filtered2) {
                QJsonObject fil2 = fil2Val.toObject();
                // Assuming "vehicles" is a JSON array in the person object
                QJsonArray vehicles = fil1["vehicles"].toArray();
                if (vehicles.contains(fil2["vehicle_no"])) {
                    QJsonObject combined;
                    combined["id"] = fil1["id"];
                    combined["name"] = fil1["name"];
                    combined["img"] = fil1["img"];
                    combined["gender"] = fil1["gender"];
                    combined["hairstyle"] = fil1["hairstyle"];
                    combined["attribute"] = fil1["attribute"];
                    combined["vehicle_no"] = fil2["vehicle_no"];
                    combined["type"] = fil2["type"];
                    combined["brand"] = fil2["brand"];
                    combined["model"] = fil2["model"];
                    combined["color"] = fil2["color"];
                    filtered_datas.append(combined);
                }
            }
        }
    } else if (!filtered1.isEmpty()) {
        for (const QJsonValue &fil1Val : filtered1) {
            filtered_datas.append(fil1Val.toObject());
        }
    } else if (!filtered2.isEmpty()) {
        for (const QJsonValue &fil2Val : filtered2) {
            QJsonObject combined;
            // Assuming you have logic to find corresponding person_id
            QJsonObject fil2 = fil2Val.toObject();
            if (fil2.contains("person_id")) {
                // p
                QJsonValue personId = fil2["person_id"];
                int Id_int = personId.toInt();
                if (!personId.isBool() && Id_int >= 0){
                // int personId = fil2["person_id"].toInt();
                    for (const QJsonValue &d1Val : datas1) {
                        QJsonObject d1 = d1Val.toObject();
                        if (d1["id"].toInt() == Id_int) {
                            combined = d1;
                            break;
                        }
                    }
                }
            }

            for (const QString &key : fil2.keys()) {
                combined.insert(key, fil2.value(key));  // Jika ada key yang sama, nilai dari fill2 akan menggantikan yang ada di combined
            }
            filtered_datas.append(combined);

        }
    }
//    qDebug() << "Datas" << filtered_datas << "\n--\n";

    if (!filtered_datas.isEmpty()) {
        QMessageBox::information(this, "Searching info", QString("Filtered data: %1").arg(filtered_datas.size()));
    } else {
        QMessageBox::critical(this, "Searching info", "No data found.");
    }
}


void ObjRealtime::show_filter() {
    // Memuat UI dialog dari file .ui
    QDialog *dialog = new QDialog(this);
    Ui::SelectData dialog_ui;
    dialog_ui.setupUi(dialog);

    dialog->setWindowTitle("Select item");
    QTableWidget *tb_show = dialog_ui.tb_show; // Tabel dari UI

    dialog_ui.label_head1->setText("All Data Filter Results");

    // Ambil data yang terfilter
    QList<QJsonObject> data_to_show = filtered_datas;
//    qDebug() << data_to_show;

    QString form_filter;
    if (!data_to_show.isEmpty()) {
        // Tentukan header tabel berdasarkan jumlah kolom
        QStringList header_items;
        if (data_to_show[0].keys().size() == 7) {
            header_items << "No." << "Name" << "Img" << "Gender" << "Hairstyle" << "Attribute" << "Vehicle No";
            form_filter = "Person";
        } else if (data_to_show[0].keys().size() == 6) {
            header_items << "Vehicle No" << "Car Type" << "Brand" << "Model" << "Color";
            form_filter = "Vehicle";
        } else {
            header_items << "No." << "Name" << "Img" << "Gender" << "Hairstyle" << "Attribute" << "Vehicle No" << "Car Type" << "Brand" << "Model" << "Color";
            form_filter = "Person_Vehicle";
        }

        // Mengatur jumlah baris dan kolom tabel
        tb_show->setRowCount(data_to_show.size());
        tb_show->setColumnCount(header_items.size());

        // Atur header tabel
        QHeaderView *header = tb_show->horizontalHeader();
        header->setMinimumHeight(34);
//        header->setDefaultAlignment(Qt::AlignCenter | Qt::TextWordWrap);

        for (int i = 0; i < header_items.size(); ++i) {
            QTableWidgetItem *hItem = new QTableWidgetItem(header_items[i]);
            tb_show->setHorizontalHeaderItem(i, hItem);
            if (header_items[i] == "No.") {
                tb_show->setColumnWidth(i, 20); // Kolom No.
            } else if (i == 1) {
                tb_show->setColumnWidth(i, 100); // Kolom Name
            } else if (i == 5 || i == 6) {
                tb_show->setColumnWidth(i, 120); // Kolom Attribute dan Vehicle No
            } else {
                header->setSectionResizeMode(i, QHeaderView::Stretch); // Stretch untuk kolom lain
            }
        }

        // Tampilkan data ke dalam tabel
        for (int row_id = 0; row_id < data_to_show.size(); ++row_id) {
            const QJsonObject &data = data_to_show[row_id];
            for (const QString &key : data.keys()) {
//                qDebug() << "data " << data.value(key).toVariant();
                QVariant data_value = data.value(key).toVariant();
                QString value = "";
                int i = 0;

                if(form_filter == "Person"){
                    // list to string
                    if (data_value.toStringList().size() > 1) {
                        QStringList attrList;
                        for (const QString &attr : data_value.toStringList()) {
                            attrList << attr;
                        }
                        QString attributesStr;
                        attributesStr = attrList.join(", ");

                        if (key == "attribute") {
                            value = attributesStr;
                            i=5;
                        } else if (key == "vehicles"){
                            value = attributesStr;
                            i=6;
                        }

                    } else {
                        if (key == "id") {
                            value = QString::number(row_id + 1);
                            i=0;
                        } else if (key == "name"){
                            value = data_value.toString();
                            i=1;
                        } else if (key == "img") {
                            value = data_value.toString();
                            i=2;
                        } else if (key == "gender") {
                            value = data_value.toString();
                            i=3;
                        } else if (key == "hairstyle") {
                            value = data_value.toString();
                            i=4;
                        } else if (key == "attribute") {
                            if(data_value.toStringList().empty()){
                                value = "None";
                            } else {
                                value = data_value.toStringList()[0];
                            }
                            i=5;
                        } else if (key == "vehicles") {
                            if(data_value.toStringList().empty()){
                                value = "None";
                            } else {
                                value = data_value.toStringList()[0];
                            }
                            i=6;
                        }
                    }
                } else if(form_filter == "Vehicle"){
                    if (key == "vehicle_no") {
                        i=0;
                    } else if (key == "type"){
                        i=1;
                    } else if (key == "brand") {
                        i=2;
                    } else if (key == "model") {
                        i=3;
                    } else if (key == "color") {
                        i=4;
                    } else if (key == "person_id") {
                        i=5;
                    }
                    value = data_value.toString();
                } else if(form_filter == "Person_Vehicle"){
                    if (data_value.toStringList().size() > 1) {
                        QStringList attrList;
                        for (const QString &attr : data_value.toStringList()) {
                            attrList << attr;
                        }
                        QString attributesStr;
                        attributesStr = attrList.join(", ");

                        if (key == "attribute") {
                            value = attributesStr;
                            i=5;
                        } else if (key == "vehicles"){
                            value = attributesStr;
                            i=6;
                        }

                    } else {
                        value = data_value.toString();
                        if (key == "id") {
                            value = QString::number(row_id + 1);
                            i=0;
                        } else if (key == "name"){
                            i=1;
                        } else if (key == "img") {
                            i=2;
                        } else if (key == "gender") {
                            i=3;
                        } else if (key == "hairstyle") {
                            i=4;
                        } else if (key == "attribute") {
                            if(data_value.toStringList().empty()){
                                value = "None";
                            } else {
                                value = data_value.toStringList()[0];
                            }
                            i=5;
                        } else if (key == "vehicle_no") {
                            i=6;
                        } else if (key == "type"){
                            i=7;
                        } else if (key == "brand") {
                            i=8;
                        } else if (key == "model") {
                            i=9;
                        } else if (key == "color") {
                            i=10;
                        }
                    }
                }


                QTableWidgetItem *it = new QTableWidgetItem(value);
                it->setTextAlignment(Qt::AlignCenter);
                tb_show->setItem(row_id, i, it);
            }
        }
    }

    // Tombol cancel untuk menutup popup
    connect(dialog_ui.cancel_btn, &QPushButton::clicked, dialog, &QDialog::close);

    dialog->exec();
}
