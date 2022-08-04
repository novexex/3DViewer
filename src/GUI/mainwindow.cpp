#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    init_settings(&file_settings);
    FILE* f2 = fopen("/Users/Shared/settings21.cfg", "r");
    if (f2) {
        fscanf(f2, "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%d\n%d\n%d", &file_settings.line_width, &file_settings.line_color[0],
        &file_settings.line_color[1], &file_settings.line_color[2], &file_settings.vertex_size, &file_settings.vertex_color[0], &file_settings.vertex_color[1],
        &file_settings.vertex_color[2], &file_settings.background_rgb1, &file_settings.background_rgb2, &file_settings.background_rgb3, &file_settings.line_type,
        &file_settings.vertex_mapping, &file_settings.projection);
        fclose(f2);
        cfg++;
    }
    ui->setupUi(this);
    this->setWindowTitle("3DViewer v1.0");
    ui->lineEdit_backgroundColor1->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_backgroundColor2->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_backgroundColor3->setAlignment(Qt::AlignHCenter);
    if (cfg) {
        ui->lineEdit_lineWidth->setText(QVariant(file_settings.line_width).toString());
        ui->lineEdit_vertexSize->setText(QVariant(file_settings.vertex_size).toString());
        ui->lineEdit_backgroundColor1->setText(QVariant(file_settings.background_rgb1).toString());
        ui->lineEdit_backgroundColor2->setText(QVariant(file_settings.background_rgb2).toString());
        ui->lineEdit_backgroundColor3->setText(QVariant(file_settings.background_rgb3).toString());
        ui->comboBox_projection->setCurrentIndex(file_settings.projection);
        ui->comboBox_lineType->setCurrentIndex(file_settings.line_type);
        ui->comboBox_vertexMapping->setCurrentIndex(file_settings.vertex_mapping);
        if (!file_settings.line_color[0] && !file_settings.line_color[1] && !file_settings.line_color[2]) {
            ui->comboBox_lineColor->setCurrentIndex(0);
        } else if (file_settings.line_color[0] && file_settings.line_color[1] && file_settings.line_color[2]) {
            ui->comboBox_lineColor->setCurrentIndex(1);
        } else if (file_settings.line_color[0] && !file_settings.line_color[1] && !file_settings.line_color[2]) {
            ui->comboBox_lineColor->setCurrentIndex(2);
        } else if (!file_settings.line_color[0] && file_settings.line_color[1] && !file_settings.line_color[2]) {
            ui->comboBox_lineColor->setCurrentIndex(3);
        } else if (!file_settings.line_color[0] && !file_settings.line_color[1] && file_settings.line_color[2]) {
            ui->comboBox_lineColor->setCurrentIndex(4);
        }
        if (!file_settings.vertex_color[0] && !file_settings.vertex_color[1] && !file_settings.vertex_color[2]) {
            ui->comboBox_vertexColor->setCurrentIndex(0);
        } else if (file_settings.vertex_color[0] && file_settings.vertex_color[1] && file_settings.vertex_color[2]) {
            ui->comboBox_vertexColor->setCurrentIndex(1);
        } else if (file_settings.vertex_color[0] && !file_settings.vertex_color[1] && !file_settings.vertex_color[2]) {
            ui->comboBox_vertexColor->setCurrentIndex(2);
        } else if (!file_settings.vertex_color[0] && file_settings.vertex_color[1] && !file_settings.vertex_color[2]) {
            ui->comboBox_vertexColor->setCurrentIndex(3);
        } else if (!file_settings.vertex_color[0] && !file_settings.vertex_color[1] && file_settings.vertex_color[2]) {
            ui->comboBox_vertexColor->setCurrentIndex(4);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Done_clicked()
{
    int errors = 0;
    int warnings = 0;

    //fill projection
    if (ui->comboBox_projection->currentIndex() == 0) {
        file_settings.projection = 0; //central
    } else {
        file_settings.projection = 1; //parallel
    }

    //fill line_width
    double tmp = ui->lineEdit_lineWidth->text().toDouble();

    if (tmp > DBL_MAX || tmp < DBL_MIN)
        warnings++;
    else
        file_settings.line_width = tmp;

    //fill vertex_size
    tmp = ui->lineEdit_vertexSize->text().toDouble();

    if (tmp > DBL_MAX || tmp < DBL_MIN)
        warnings++;
    else
        file_settings.vertex_size = tmp;

    //fill line_type
    if (ui->comboBox_lineType->currentIndex() == 0) {
        file_settings.line_type = 0; //solid lines
    } else {
        file_settings.line_type = 1; //dashed lines
    }

    //fill line_color
    switch (ui->comboBox_lineColor->currentIndex()) {
    case 0: //black
        file_settings.line_color[0] = 0;
        file_settings.line_color[1] = 0;
        file_settings.line_color[2] = 0;
    break;

    case 1: //green
        file_settings.line_color[0] = 1;
        file_settings.line_color[1] = 1;
        file_settings.line_color[2] = 1;
    break;

    case 2: //red
        file_settings.line_color[0] = 1;
        file_settings.line_color[1] = 0;
        file_settings.line_color[2] = 0;
    break;

    case 3: //green
        file_settings.line_color[0] = 0;
        file_settings.line_color[1] = 1;
        file_settings.line_color[2] = 0;
    break;

    case 4: //blue
        file_settings.line_color[0] = 0;
        file_settings.line_color[1] = 0;
        file_settings.line_color[2] = 1;
    break;
    }

    //fill vertex_mapping
    switch (ui->comboBox_vertexMapping->currentIndex()) {
        case 0: //no
            file_settings.vertex_mapping = 0;
        break;

        case 1: //circle
            file_settings.vertex_mapping = 1;
        break;

        case 2: //square
            file_settings.vertex_mapping = 2;
        break;
    }

    //fill vertex_color
    switch (ui->comboBox_vertexColor->currentIndex()) {
        case 0: //black
            file_settings.vertex_color[0] = 0;
            file_settings.vertex_color[1] = 0;
            file_settings.vertex_color[2] = 0;
        break;

        case 1: //green
            file_settings.vertex_color[0] = 1;
            file_settings.vertex_color[1] = 1;
            file_settings.vertex_color[2] = 1;
        break;

        case 2: //red
            file_settings.vertex_color[0] = 1;
            file_settings.vertex_color[1] = 0;
            file_settings.vertex_color[2] = 0;
        break;

        case 3: //green
            file_settings.vertex_color[0] = 0;
            file_settings.vertex_color[1] = 1;
            file_settings.vertex_color[2] = 0;
        break;

        case 4: //blue
            file_settings.vertex_color[0] = 0;
            file_settings.vertex_color[1] = 0;
            file_settings.vertex_color[2] = 1;
        break;
    }

    //fill background_color
    QByteArray tmp_rbg1 = ui->lineEdit_backgroundColor1->text().toLocal8Bit();
    char* rgb1 = tmp_rbg1.data();
    QByteArray tmp_rbg2 = ui->lineEdit_backgroundColor2->text().toLocal8Bit();
    char* rgb2 = tmp_rbg2.data();
    QByteArray tmp_rbg3 = ui->lineEdit_backgroundColor3->text().toLocal8Bit();
    char* rgb3 = tmp_rbg3.data();

    if (rgb_processing(rgb1) || rgb_processing(rgb2) || rgb_processing(rgb3)) {
        warnings++;
    } else {
        file_settings.background_rgb1 = ui->lineEdit_backgroundColor1->text().toDouble();
        file_settings.background_rgb2 = ui->lineEdit_backgroundColor2->text().toDouble();
        file_settings.background_rgb3 = ui->lineEdit_backgroundColor3->text().toDouble();
    }

    //fill file_path & file_name
    if (ui->lineEdit_FilePath->text().isEmpty()) {
        errors++;
    } else {
        file_settings.file_path = ui->lineEdit_FilePath->text();
        QByteArray temp = ui->lineEdit_FilePath->text().toLocal8Bit();
        char* absolute_path = temp.data();
        char file_name[1024] = "\0";
        get_file_name(absolute_path, file_name);
        file_settings.file_name = file_name;
    }

    QByteArray char_tmp = ui->lineEdit_FilePath->text().toLocal8Bit();
    char* path_file = char_tmp.data();

    char file_name[1024] = "\0";
    data_t obj;
    FILE *one = fopen(path_file, "r");
    if (one == NULL) {
        errors++;
    } else {
        file_settings.file_path = ui->lineEdit_FilePath->text();
        get_file_name(path_file, file_name);
        file_settings.file_name = file_name;
    }

    //errors & warnings processing
    if (errors) {
        QMessageBox::critical(this, "Error", "Can't open the file.\nPlease try again.");
    } else if (warnings) {
        QMessageBox::warning(this, "Warning", "Invalid settings set.\nPlease try again.");
    } else {
        count_of_vertexes(one, &obj);
        rewind(one);
        fill_matrix(&obj, one);

        Widget *win3D = new Widget;

        file_settings.vertex_count = obj.vertex_cnt;
        file_settings.connections_count = obj.facet_cnt;
        file_settings.vertex_array = obj.dst;
        file_settings.connections_array = obj.polyg;
        file_settings.background_rgb1 = ui->lineEdit_backgroundColor1->text().toInt();
        file_settings.background_rgb2 = ui->lineEdit_backgroundColor2->text().toInt();
        file_settings.background_rgb3 = ui->lineEdit_backgroundColor3->text().toInt();

        FILE *f = fopen("/Users/Shared/settings21.cfg", "w");
        if (f) {
            fprintf(f, "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%d\n%d\n%d", file_settings.line_width, file_settings.line_color[0],
            file_settings.line_color[1], file_settings.line_color[2], file_settings.vertex_size, file_settings.vertex_color[0], file_settings.vertex_color[1],
            file_settings.vertex_color[2], file_settings.background_rgb1, file_settings.background_rgb2, file_settings.background_rgb3, file_settings.line_type,
            file_settings.vertex_mapping, file_settings.projection);
            fflush(f);
            fclose(f);
        }

        Dialog *dialog_window = new Dialog(file_settings);
        win3D->file_settings_w = file_settings;
        dialog_window->curr_3D = win3D;
        dialog_window->obj_d = obj;

        win3D->show();
        dialog_window->show();
    }
}

void MainWindow::init_settings(settings_t *file_settings) {
    file_settings->file_name = 0;
    file_settings->file_path = 0;
    file_settings->background_rgb1 = 0;
    file_settings->background_rgb2 = 0;
    file_settings->background_rgb3 = 0;
    file_settings->line_color[0] = 0;
    file_settings->line_color[1] = 0;
    file_settings->line_color[2] = 0;
    file_settings->line_type = 0;
    file_settings->vertex_color[0] = 0;
    file_settings->vertex_color[1] = 0;
    file_settings->vertex_color[2] = 0;
    file_settings->vertex_size = 0;
    file_settings->projection = 0;
    file_settings->vertex_mapping = 0;
    file_settings->vertex_count = 0;
    file_settings->connections_count = 0;
    file_settings->line_width = 0;
    file_settings->connections_array = 0;
    file_settings->vertex_array = 0;
}
