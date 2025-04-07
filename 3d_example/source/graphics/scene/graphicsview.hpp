#ifndef _fms32183jdaniriolam
#define _fms32183jdaniriolam

#include <QGraphicsView>

class GraphicsView : public QGraphicsView {
Q_OBJECT
public:
    GraphicsView(QWidget* parent);
    ~GraphicsView() override = default;

protected:
    void wheelEvent(QWheelEvent* event) override;
};

#endif