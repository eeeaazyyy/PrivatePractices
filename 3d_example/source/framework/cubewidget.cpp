#include <QMouseEvent>

#include "cubewidget.hpp"

CubeWidget::CubeWidget()
    : QOpenGLWidget(), QOpenGLFunctions(), texture_(nullptr), projection_(),
      angularSpeed_(0) {
}

CubeWidget::~CubeWidget() {
    makeCurrent();
    delete texture_;
    // delete geometries_;
    doneCurrent();
}

void CubeWidget::mousePressEvent(QMouseEvent *event) {
    // Save mouse press position
    mousePressPositionContainer_ = QVector2D(event->position());
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *event) {
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(event->position()) - mousePressPositionContainer_;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxisContainer_ = (rotationAxisContainer_ * angularSpeed_ + n * acc).normalized();

    // Increase angular speed
    angularSpeed_ += acc;
}

void CubeWidget::timerEvent(QTimerEvent *event) {
    // Decrease angular speed (friction)
    angularSpeed_ *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed_ < 0.01) {
        angularSpeed_ = 0.0;
    } else {
        // Update rotation
        rotation_ = QQuaternion::fromAxisAndAngle(rotationAxisContainer_, angularSpeed_) * rotation_;

        // Request an update
        update();
    }
}

void CubeWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    // timer.start(12, this);
}

void CubeWidget::resizeGL(int width, int height) {
    // Calculate aspect ratio
    qreal aspect = qreal(width) / qreal(height ? height : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection_.setToIdentity();

    // Set perspective projection
    projection_.perspective(fov, aspect, zNear, zFar);
}

void CubeWidget::paintGL() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    texture_->bind();
    openGlProgram_.bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation_);

    // Set modelview-projection matrix
    openGlProgram_.setUniformValue("mvp_matrix", projection_ * matrix);

    // Use texture unit 0 which contains cube.png
    openGlProgram_.setUniformValue("texture", 0);

    // Draw cube geometry
    // geometries->drawCubeGeometry(&program);
}

void CubeWidget::initShaders() {
    // Compile vertex shader
    if (!openGlProgram_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!openGlProgram_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!openGlProgram_.link())
        close();

    // Bind shader pipeline for use
    if (!openGlProgram_.bind())
        close();
}

void CubeWidget::initTextures() {
    // Load cube.png image
    texture_ = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture_->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture_->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture_->setWrapMode(QOpenGLTexture::Repeat);
}