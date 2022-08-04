#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    setGeometry(1050, 380, 800, 600);
    this->setWindowTitle("3DViewer v1.0");
}

void Widget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (file_settings_w.projection)
        glOrtho(-1, 1, -1, 1, -1, 100);
    else
        glFrustum(-2, 2, -2, 2, 1, 100);
}

void Widget::paintGL() {
    glClearColor(file_settings_w.background_rgb1, file_settings_w.background_rgb2, file_settings_w.background_rgb3, 1);
    glColor3d(file_settings_w.line_color[0], file_settings_w.line_color[1], file_settings_w.line_color[2]);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (file_settings_w.line_type) {
        glLineStipple(2, 0x00F0);
        glEnable(GL_LINE_STIPPLE);
    }
    glLineWidth(file_settings_w.line_width);
    if (file_settings_w.projection)
        glTranslatef(0, 0, 0);
    else
        glTranslatef(0, 0, -8);
    glTranslatef(0, 0, -8);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);
    drawObject();
}

void Widget::drawObject() {
    glVertexPointer(3, GL_DOUBLE, 0, file_settings_w.vertex_array);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, file_settings_w.connections_count, GL_UNSIGNED_INT, file_settings_w.connections_array);
    glDisableClientState(GL_VERTEX_ARRAY);

    if (file_settings_w.vertex_mapping) {
        if (file_settings_w.vertex_mapping == 2 && file_settings_w.projection)
            draw_square_vert_paral();
        else if (file_settings_w.vertex_mapping == 2 && !file_settings_w.projection)
            draw_square_vert_central();
        else if (file_settings_w.vertex_mapping == 1 && !file_settings_w.projection)
            draw_dots_central();
        else if (file_settings_w.vertex_mapping == 1 && file_settings_w.projection)
            draw_dots_paral();
    }
}

void Widget::draw_square_vert_paral() {
    double size = file_settings_w.vertex_size / 100;
    for (int i = 0; i < file_settings_w.vertex_count * 3; i++) {
        if (i % 3 == 0) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(file_settings_w.vertex_color[0], file_settings_w.vertex_color[1], file_settings_w.vertex_color[2]);
            glVertex2f(file_settings_w.vertex_array[i] - size, file_settings_w.vertex_array[i + 1] - size);
            glVertex2f(file_settings_w.vertex_array[i] - size, file_settings_w.vertex_array[i + 1] + size);
            glVertex2f(file_settings_w.vertex_array[i] + size, file_settings_w.vertex_array[i + 1] + size);
            glVertex2f(file_settings_w.vertex_array[i] + size, file_settings_w.vertex_array[i + 1] - size);
            glEnd();
        }
    }
}

void Widget::draw_square_vert_central() {
    double x, y;
    double size = file_settings_w.vertex_size / 100;
    for (int i = 0; i < file_settings_w.vertex_count * 3; i++) {
        if (i % 3 == 0) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(file_settings_w.vertex_color[0], file_settings_w.vertex_color[1], file_settings_w.vertex_color[2]);
            x = file_settings_w.vertex_array[i] / (1 - (file_settings_w.vertex_array[i+2] / 8));
            y = file_settings_w.vertex_array[i+1] / (1 - (file_settings_w.vertex_array[i+2] / 8));
            glVertex2f(x - size, y - size);
            glVertex2f(x - size, y + size);
            glVertex2f(x + size, y + size);
            glVertex2f(x + size, y - size);
            glEnd();
        }
    }
}

void Widget::draw_dots_central() {
    double x,y;
    glPointSize(file_settings_w.vertex_size);
    glEnable(GL_POINT_SMOOTH);
    for (int i = 0; i < file_settings_w.vertex_count * 3; i++) {
        if (i % 3 == 0) {
            glBegin(GL_POINTS);
            glColor3f(file_settings_w.vertex_color[0], file_settings_w.vertex_color[1], file_settings_w.vertex_color[2]);
            x = file_settings_w.vertex_array[i] / (1 - (file_settings_w.vertex_array[i+2] / 8));
            y = file_settings_w.vertex_array[i+1] / (1 - (file_settings_w.vertex_array[i+2] / 8));
            glVertex2f(x, y);
            glEnd();
        }
    }
    glDisable(GL_POINT_SMOOTH);
}

void Widget::draw_dots_paral() {
    glPointSize(file_settings_w.vertex_size);
    glEnable(GL_POINT_SMOOTH);
    for (int i = 0; i < file_settings_w.vertex_count * 3; i++) {
        if (i % 3 == 0) {
            glBegin(GL_POINTS);
            glColor3f(file_settings_w.vertex_color[0], file_settings_w.vertex_color[1], file_settings_w.vertex_color[2]);
            glVertex2f(file_settings_w.vertex_array[i], file_settings_w.vertex_array[i+1]);
            glEnd();
        }
    }
    glDisable(GL_POINT_SMOOTH);
}

void Widget::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* mo) {
    xRot = 1 / M_PI*(mo->pos().y()-mPos.y());
    yRot = 1 / M_PI*(mo->pos().x()-mPos.x());
    update();
}
