#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(settings_t file_settings) :
    QDialog(nullptr),
    ui(new Ui::Dialog)
{
    file_settings_d = file_settings;
    setGeometry(1045, 1009, 800, 600);
    ui->setupUi(this);
    this->setWindowTitle("Viewer Controller");
    ui->label_FileName->setText(ui->label_FileName->text() + " " + file_settings_d.file_name);
    ui->label_IndexesCount->setText(ui->label_IndexesCount->text() + " " + QVariant(file_settings_d.connections_count).toString());
    ui->label_VertexesCount->setText(ui->label_VertexesCount->text() + " " + QVariant(file_settings_d.vertex_count).toString());
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_plus_xAxis_clicked()
{
    move_x(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_plus_yAxis_clicked()
{
    move_y(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_plus_zAxis_clicked()
{
    move_z(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_minus_xAxis_clicked()
{
    move_x(&obj_d, -0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_minus_yAxis_clicked()
{
    move_y(&obj_d, -0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_minus_zAxis_clicked()
{
    move_z(&obj_d, -0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_rotate_xAxis_clicked()
{
    rotation_by_ox(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_zoomIn_clicked()
{
    zoom(&obj_d, 1.2);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_zoomOut_clicked()
{
    zoom(&obj_d, 0.8);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_rotate_yAxis_clicked()
{
    rotation_by_oy(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_rotate_zAxis_clicked()
{
    rotation_by_oz(&obj_d, 0.5);
    update();
    record_gif();
    this->activateWindow();
    curr_3D->activateWindow();
}


void Dialog::on_pushButton_makeScreenshot_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "BMP (*.bmp);; JPEG (*.jpeg)");
    curr_3D->grab().save(file);
}


void Dialog::on_pushButton_startScreencast_clicked()
{
    record = 1;
}

void Dialog::record_gif()
{
    if (record == 1)
        mas_image.push_back(curr_3D->grab().toImage());
}

void Dialog::on_pushButton_stopScreencast_clicked()
{
    record = 0;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save screenshot"), "", tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
    QGifImage gif(QSize(1500, 1000));
    QVector<QRgb> ctable;
    ctable << qRgb(255, 255, 255)
           << qRgb(0, 0, 0)
           << qRgb(255, 0, 0)
           << qRgb(0, 255, 0)
           << qRgb(0, 0, 255)
           << qRgb(255, 255, 0)
           << qRgb(0, 255, 255)
           << qRgb(255, 0, 255);

    gif.setGlobalColorTable(ctable, Qt::black);
    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);

    for (QVector<QImage>::Iterator img = mas_image.begin(); img != mas_image.end(); ++img) {
        gif.addFrame(*img);
    }
    gif.save(fileName);
}

