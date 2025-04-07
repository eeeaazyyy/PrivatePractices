#ifndef _0032gfshkfjug3oj2hfdajsvd32__
#define _0032gfshkfjug3oj2hfdajsvd32__

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    using QOpenGLWidget::QOpenGLWidget;
    CubeWidget();
    ~CubeWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void timerEvent(QTimerEvent *event) override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QOpenGLShaderProgram openGlProgram_;
    QOpenGLTexture *texture_;

    QMatrix4x4 projection_;
    QVector2D mousePressPositionContainer_;
    QVector3D rotationAxisContainer_;
    qreal angularSpeed_;
    QQuaternion rotation_;
};

#endif