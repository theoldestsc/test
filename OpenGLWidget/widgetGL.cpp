#include "widgetGL.h"
#include <QOpenGLFunctions_4_5_Core>
#include "shader.h"
#include <QKeyEvent>

void GenTriangleBuffer(QOpenGLFunctions_4_5_Core* f)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,    0.7f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.7f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      0.7f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      0.7f, 0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f,     0.0f, 0.7f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.7f, 0.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.7f, 0.0f,
        0.5f, -0.5f, 0.5f,      0.0f, 0.7f, 0.0f,

        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 0.7f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 0.7f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.7f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.7f,

        -0.5f, 0.5f, 0.5f,      0.7f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,     0.7f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.7f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.7f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,     0.0f, 0.7f, 0.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.7f, 0.0f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.7f, 0.0f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.7f, 0.0f,

        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.7f,
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.7f,
        0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.7f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 0.7f,

        -0.5f, -0.5f, -0.5f,    0.7f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.7f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      0.7f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      0.7f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,     0.0f, 0.7f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.7f, 0.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 0.7f, 0.0f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.7f, 0.0f,

        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 0.7f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 0.7f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.7f,
        -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, 0.7f,
    };

    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void MyGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    this->f = new QOpenGLFunctions_4_5_Core;
    this->f->initializeOpenGLFunctions();
    this->setGeometry(100, 100, 800, 600);
    this->f->glViewport(this->geometry().x(),
                            this->geometry().y(),
                            this->geometry().width(),
                            this->geometry().height());
    unsigned int VBO, vertexShader, fragmentShader, EBO;
    this->f->glGenVertexArrays(1, &VAO);
    this->f->glGenBuffers(1, &VBO);
    this->f->glGenBuffers(1, &EBO);
    this->f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->f->glBindVertexArray(VAO);


    this->f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    this->f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    GenTriangleBuffer(f);
    shader = new Shader("D:\\OpenGL\\Third\\OpenGLWidget\\vertexSh.vert",
                        "D:\\OpenGL\\Third\\OpenGLWidget\\fragmentSh.fsh");

    this->f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                                        (void*)0);
    this->f->glEnableVertexAttribArray(0);

    this->f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                                        (void*)(3*sizeof(float)));
    this->f->glEnableVertexAttribArray(1);



}

void MyGLWidget::resizeGL(int w, int h)
{
    if(this->f)
        this->f->glViewport(0,
                            0,
                            this->geometry().width(),
                            this->geometry().height());

}

void MyGLWidget::paintGL()
{
    /*glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans,
                        glm::radians(90.0f),
                        glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/
    /*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);*/
    /*glm::mat4 view;
    view = glm::lookAt(cameraPos,
                       cameraDirection,
                       cameraUp);*/

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f),
    glm::vec3(1.0f, 0.0f, 0.0f));
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    // note that we’re translating the scene in the reverse direction
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
                                  100.0f);


    int modelLoc = this->f->glGetUniformLocation(shader->ID, "model");
    this->f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    modelLoc = this->f->glGetUniformLocation(shader->ID, "view");
    this->f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(view));
    modelLoc = this->f->glGetUniformLocation(shader->ID, "projection");
    this->f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //int vertexColorLocation = this->f->glGetUniformLocation(shaderProgram, "ourColor");
    this->f->glEnable(GL_DEPTH_TEST);

    this->f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->shader->use();
    //this->f->glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    this->f->glBindVertexArray(VAO);
    //this->f->glDrawArrays(GL_TRIANGLES, 0, 36);
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle),
        glm::vec3(1.0f, 0.3f, 0.5f));
        int modelLoc = this->f->glGetUniformLocation(shader->ID, "model");
        this->f->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        this->f->glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

void MyGLWidget::keyPressEvent(QKeyEvent *ev)
{
    const float cameraSpeed = 0.25f;
    qDebug() << ev->key();
    if(ev->key() == Qt::Key_W)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if(ev->key() == Qt::Key_S)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    else if(ev->key() == Qt::Key_A)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    else if(ev->key() == Qt::Key_D)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

}

MyGLWidget::~MyGLWidget()
{
    delete f;
}
