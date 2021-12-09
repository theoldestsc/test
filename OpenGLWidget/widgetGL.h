#ifndef WIDGET_H
#define WIDGET_H


#include <QOpenGLWidget>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class QOpenGLFunctions_4_5_Core;
class QKeyEvent;

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) { };
    ~MyGLWidget();
private:
    QOpenGLFunctions_4_5_Core* f = nullptr;
    unsigned int shaderProgram{}, VAO{};
    Shader* shader = nullptr;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *ev) override;
};

#endif // WIDGET_H
