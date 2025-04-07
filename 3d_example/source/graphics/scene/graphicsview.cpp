#include <QWheelEvent>

#include "graphicsview.hpp"

GraphicsView::GraphicsView(QWidget *parent) 
        : QGraphicsView(parent) {
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHint(QPainter::Antialiasing);
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    // Масштабирование при прокрутке колеса мыши
    double factor = 1.1;
    if(event->angleDelta().y() < 0)
        factor = 1.0 / factor;
    
    scale(factor, factor);
}
