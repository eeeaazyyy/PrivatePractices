#ifndef __39243jufsfuirp3fjnvnfuvoii
#define __39243jufsfuirp3fjnvnfuvoii

#include <QWidget>
#include <QSharedPointer>

#include <QGraphicsScene>

class GraphicsView;

class GraphicsEditor : public QWidget {
Q_OBJECT
public:
    explicit GraphicsEditor(QWidget* parent = nullptr);
    ~GraphicsEditor() override = default;

private:
QRect calculateSize() const;

private slots:
    void addEllipse();
    void addRect();
    void saveSvgScheme();


private:
    QGraphicsScene *scene_;
    GraphicsView *graphicsView_;
};

#endif