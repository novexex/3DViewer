#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <float.h>

extern "C"
{
    #include "viewer.h"
    #include "validation.h"
}

typedef struct {
    QString file_path;
    QString file_name;
    double line_width;
    double line_color[3];
    double vertex_size;
    double vertex_color[3];
    double background_rgb1, background_rgb2, background_rgb3;
    double* vertex_array;
    unsigned* connections_array;
    int vertex_count;
    int connections_count;
    int vertex_mapping;
    int line_type;
    int projection;
} settings_t;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Done_clicked();

private:
    QWidget *tmp;
    Ui::MainWindow *ui;
    void init_settings(settings_t *file_settings);
    settings_t file_settings;
    int cfg;
};

#endif // MAINWINDOW_H
