#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,VBO(QOpenGLBuffer::VertexBuffer)
    ,EBO(QOpenGLBuffer::IndexBuffer)
    ,texture(QOpenGLTexture::Target2D)

{
}

Widget::~Widget()
{
    makeCurrent();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();        //初始化OpenGL解析函数
    glClearColor(0.0f,0.5f,0.9f,1.0f);  //设置缓冲区的清除颜色
    glClear(GL_COLOR_BUFFER_BIT);       //根据设置的颜色设置屏幕
    VAO.create();
    VAO.bind();
    VBO.create();
    VBO.bind();
    EBO.create();
    EBO.bind();
    uint elements[]={0,1,2,3};
    EBO.allocate(elements,sizeof(elements));
    GLfloat vertices[]={
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // 右上角
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 右下角
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // 左上角
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
    };
    VBO.allocate(vertices,sizeof(vertices));
    texture.create();
    texture.setData(QImage(":/123.jpg"));


    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gl.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gl.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray("pos");  //开启着色器程序的“Pos”属性
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,3,5*sizeof (float)); //设置顶点数据的来源

    shaderProgram.enableAttributeArray(1);
    shaderProgram.setAttributeBuffer(1,GL_FLOAT,3*sizeof (float),2,5*sizeof (float));
    VAO.release();
    VBO.release();
    EBO.release();
}

void Widget::paintGL()
{
    shaderProgram.bind();
    texture.bind(0);                                //将纹理对象绑定到0号纹理单元
    shaderProgram.setUniformValue("texture",0);     //设置采样器[texture]从0号纹理单元中读取数据

    QOpenGLVertexArrayObject::Binder bind(&VAO);
    glDrawElements(GL_TRIANGLE_STRIP/*GL_POINTS*/,4,GL_UNSIGNED_INT,nullptr);
    //glDrawArrays(GL_TRIANGLE_STRIP/*GL_POINTS*/,0,4);
    //glDrawArrays(GL_POINTS, 0, 1);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

