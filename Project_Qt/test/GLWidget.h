#ifndef _GLWIDGET_H_
#define _GLWIDGET_H_

#include <QtOpenGL/QGLWidget>
#include "ui_GLWidget_Form.h"

class GLWidget: public QGLWidget
{
    Q_OBJECT
    public:
    GLWidget();
    GLWidget(QWidget* parent);
    private:
    
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();
//public:
    Ui::Widget* ui;
};

#endif