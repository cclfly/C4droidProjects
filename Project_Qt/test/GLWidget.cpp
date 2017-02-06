#include "GLWidget.h"

GLWidget::GLWidget():ui(new Ui::Widget)
{
    ui->setupUi(this);
    setLayout(ui->layout);
    raise();
}

GLWidget::GLWidget(QWidget *parent)
:QGLWidget(parent)
{
	raise();
}

void GLWidget::initializeGL()
{
    glClearColor(0.4f,0.8f,1.0f,1.0f);
}

void GLWidget::resizeGL(int w,int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}