#include <QVBoxLayout>
#include <QPushButton>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSvgGenerator>
#include <QFileDialog>

#include <graphicsview.hpp>

#include "graphicseditor.hpp"

GraphicsEditor::GraphicsEditor(QWidget *parent)
        : QWidget(parent), graphicsView_(new GraphicsView(this)),
                scene_(new QGraphicsScene(this)) {
    auto* layout = new QVBoxLayout(this);

    scene_->setSceneRect(-400, -300, 800, 600);
    scene_->setBackgroundBrush(QBrush(QColor::fromRgb(138, 158, 255)));

    graphicsView_->setScene(scene_);
    graphicsView_->setMinimumSize(800, 600);

    auto* addRectButton = new QPushButton("Add Rect");
    auto* addTriangleButton = new QPushButton("Add Triangle");
    auto* saveSvgButton = new QPushButton("Save SVG scheme");


    layout->addWidget(graphicsView_);
    layout->addWidget(addRectButton);
    layout->addWidget(addTriangleButton);
    layout->addWidget(saveSvgButton);

    connect(addRectButton, &QPushButton::clicked, this, &GraphicsEditor::addRect);
    connect(addTriangleButton, &QPushButton::clicked, this, &GraphicsEditor::addEllipse);
    connect(saveSvgButton, &QPushButton::clicked, this, &GraphicsEditor::saveSvgScheme);

    setLayout(layout);
}

QRect GraphicsEditor::calculateSize() const {
    qreal minX = std::numeric_limits<qreal>::max();
        qreal minY = std::numeric_limits<qreal>::max();
        qreal maxX = std::numeric_limits<qreal>::min();
        qreal maxY = std::numeric_limits<qreal>::min();
        
        QList<QGraphicsItem*> items = scene_->items(Qt::SortOrder::DescendingOrder);
        
        foreach (QGraphicsItem* item, items) {
            QRectF itemRect = item->sceneBoundingRect();
            
            // Находим крайние точки всех элементов
            minX = qMin(minX, itemRect.left());
            minY = qMin(minY, itemRect.top());
            maxX = qMax(maxX, itemRect.right());
            maxY = qMax(maxY, itemRect.bottom());
        }
        
        // Создаем финальный QRectF с правильными границами
        QRectF totalRect(minX, minY, maxX - minX, maxY - minY);
        
        return totalRect.toRect();
}

void GraphicsEditor::addEllipse() {
    QGraphicsEllipseItem* ellipse = scene_->addEllipse(-50, -50, 100, 100);
    ellipse->setBrush(Qt::red);
    ellipse->setPos(200, 0);
    ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void GraphicsEditor::addRect() {
    QGraphicsRectItem* rect = scene_->addRect(-100, -50, 200, 100);
    rect->setBrush(Qt::blue);
    rect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void GraphicsEditor::saveSvgScheme() {
    Q_ASSERT(graphicsView_);
    if (!graphicsView_) { return; }

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export to SVG", QString(), "SVG files (*.svg)");
    if (fileName.isEmpty()) { return; }

    QSvgGenerator generator;
    generator.setFileName(fileName);
    //generator.setSize(QSize(graphicsView_->width(), graphicsView_->height()));
    generator.setSize(calculateSize().size());
    generator.setViewBox(calculateSize());
    generator.setTitle("Test!");
    generator.setDescription("Test!");

    QPainter painter;
    painter.begin(&generator);
    graphicsView_->render(&painter);
    painter.end();
}

