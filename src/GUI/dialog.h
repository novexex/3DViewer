#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <float.h>
#include <QFileDialog>
#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include "mainwindow.h"
#include "widget.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(settings_t file_settings);
    data_t obj_d;
    settings_t file_settings_d;
    int vertex_count;
    int connection_count;
    QString file_name;
    Widget *curr_3D;
    ~Dialog();
    QVector<QImage> mas_image;
    int record;


private slots:
    void on_pushButton_plus_xAxis_clicked();

    void on_pushButton_plus_yAxis_clicked();

    void on_pushButton_plus_zAxis_clicked();

    void on_pushButton_minus_xAxis_clicked();

    void on_pushButton_minus_yAxis_clicked();

    void on_pushButton_minus_zAxis_clicked();

    void on_pushButton_rotate_xAxis_clicked();

    void on_pushButton_zoomIn_clicked();

    void on_pushButton_zoomOut_clicked();

    void on_pushButton_rotate_yAxis_clicked();

    void on_pushButton_rotate_zAxis_clicked();

    void on_pushButton_makeScreenshot_clicked();

    void on_pushButton_startScreencast_clicked();

    void record_gif();

    void on_pushButton_stopScreencast_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
