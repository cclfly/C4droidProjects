#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLShader>
#include <QVector>
#include <QVector2D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QTimer>

class MainWindow;

class OpenGLWidget:public QGLWidget
{
    Q_OBJECT
    QTimer* timer;
    QVector<QVector2D> vertices;
    QVector<QVector4D> vertex_color;
    
    QMatrix4x4 m,v,p;
    
    GLuint m_id,v_id,p_id;
    
    QGLShaderProgram program;
    public:
    QString gl_version;
    QString log[3];
    GLfloat omega=1.0f;
    
    OpenGLWidget(QWidget* parent):QGLWidget(parent)
    {
        setAutoBufferSwap(false);
        timer=new QTimer(this);
        timer->setInterval(16);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    }
    
    void initializeGL()
    {
        vertices<<QVector2D(0,1)<<QVector2D(-1,-1)<<QVector2D(1,-1);
        vertex_color<<QVector4D(1,0,0,1)<<QVector4D(0,1,0,1)<<QVector4D(0,0,1,1);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.4,0.8,1.0,1.0);
        gl_version=QString((const char*)glGetString(GL_VERSION));
        
        QGLShader* vert=new QGLShader(QGLShader::Vertex,this);
        vert->compileSourceCode(
                                "attribute vec4 v_pos;"
                                "attribute vec4 v_color;"
                                "varying vec4 a_color;"
                                "uniform mat4 m,v,p;"
                                "void main(){"
                                "gl_Position=m*v_pos;"
                                "a_color=v_color;"
                                "}");
           log[0]=vert->log();
           
          QGLShader* frag=new QGLShader(QGLShader::Fragment,this);
          frag->compileSourceCode(
                                  "varying vec4 a_color;"
                                  "void main(){"
                                  "gl_FragColor=a_color;"
                                  "}");
          log[1]=frag->log();
          
           program.addShader(vert);
           program.addShader(frag);
           program.bindAttributeLocation("v_pos",0);
           program.bindAttributeLocation("v_color",1);
           program.link();
           log[2]=program.log();
           
           program.setAttributeArray(0,vertices.constData());
           program.setAttributeArray(1,vertex_color.constData());
           program.enableAttributeArray(0);
           program.enableAttributeArray(1);
           program.bind();
           
//           p.perspective(45.0f,(float)width()/height(),0.1f,100.0f);
//          v.lookAt(QVector3D(0.0,0.0,1.0),QVector3D(0.0,-0.5,0.0),QVector3D(0.0,1.0,0.0));
           
           m_id=program.uniformLocation("m");
//           v_id=program.uniformLocation("v");
//           p_id=program.uniformLocation("p");
           
//           program.setUniformValue(v_id,v);
//           program.setUniformValue(p_id,p);
           timer->start();
    }
    
    void resizeGL(int w, int h)
     {
         glViewport(0, 0, (GLint)w, (GLint)h);
         p.perspective(45.0f,(float)w/h,0.1f,100.0f);
         program.setUniformValue(p_id,p);
     }
    
    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        m.rotate(omega,QVector3D(0,1,0));
        program.setUniformValue(m_id,m);
        
        glDrawArrays(GL_TRIANGLES,0,vertices.size());
        swapBuffers();
    }
    
    void moveEvent(QMoveEvent& e)
    {
    }
    
    void setOmega(int v)
    {
        omega=v;
    }
};

class MainWindow:public QMainWindow
{
    Q_OBJECT
    public:
    QVBoxLayout* layout,*sub_layout;
    QHBoxLayout* sub2_layout;
    QLabel* label;
    QPushButton* button,*log_button;
    QWidget* qw;
    QSpinBox* qsb;
    QSlider* qs;
    OpenGLWidget *gw;
    
    MainWindow(QWidget* parent=0):QMainWindow(parent)
    {
        qw=new QWidget(this);
        label = new QLabel("OpenGL(ES) Information",this);
        label->setStyleSheet("QLabel{color:#66ccff;font-size:35px;};");
        button=new QPushButton("GL Version",this);
        log_button=new QPushButton("Shader Compile Log",this);
        gw=new OpenGLWidget(this);
        qsb=new QSpinBox(this);
        qs=new QSlider(Qt::Horizontal,this);
        qsb->setRange(1,30);
        qs->setRange(1,30);
        connect(button,&QPushButton::clicked,label,[=]
        {
             QString text=QString("OpenGL(ES) Version:\n%1").arg(gw->gl_version);
            label->setText(text);
        });
        connect(log_button,&QPushButton::clicked,label,[=]{
            QString text=QString("%1\n%2\n%3\nGLWidget:\n--w:%4\n--h:%5").arg(gw->log[0]).arg(gw->log[1]).arg(gw->log[2]).arg(gw->width()).arg(gw->height());
            label->setText(text);
        });
        connect(qsb,SIGNAL(valueChanged(int)),qs,SLOT(setValue(int)));
        connect(qs,SIGNAL(valueChanged(int)),qsb,SLOT(setValue(int)));
        connect(qsb,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),gw,&OpenGLWidget::setOmega); 
        
        layout=new QVBoxLayout(this);
        sub_layout=new QVBoxLayout(this);
        sub2_layout=new QHBoxLayout(this);
        
        sub_layout->addWidget(label);
        sub_layout->addWidget(button);
        sub_layout->addWidget(log_button);
        sub2_layout->addWidget(qsb);
        sub2_layout->addWidget(qs);
        sub_layout->addLayout(sub2_layout);
        layout->addLayout(sub_layout);
        layout->addWidget(gw);
        qw->setLayout(layout);
        setCentralWidget(qw);
    }    
    
};
 
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);    
    MainWindow mw;
    mw.show();
    return app.exec();
}

#include <QTOpenGL.cpp.moc>