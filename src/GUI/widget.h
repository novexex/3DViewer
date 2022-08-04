#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QWidget>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    settings_t file_settings_w;

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    void drawObject();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void draw_dots_central();
    void draw_square_vert_paral();
    void draw_square_vert_central();
    void draw_dots_paral();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
};

#endif // WIDGET_H
