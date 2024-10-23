#ifndef CAMSELECTION_H
#define CAMSELECTION_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QRadioButton>
//#include <opencv2/opencv.hpp>

namespace Ui {
class CamSelection;
}

class CamSelection : public QWidget
{
    Q_OBJECT

public:
    explicit CamSelection(QWidget *parent = nullptr);
    ~CamSelection();

private slots:
    void selectedRow(int rowIdx, QRadioButton *radioWidget);
    void displayVid();

private:
    Ui::CamSelection *ui;
    QList<QStringList> datas;
//    cv::VideoCapture camera;
    QTimer *timer;
    QLabel *label_cam;
};

#endif // CAMSELECTION_H
