#include <graphicseditor.hpp>

#include "QLineEdit"

#include "mainwindow.hpp"

#include "include/delaywidgetcontroller.hpp"
#include "test/alertTest/alertmodel.hpp"

#include "include/graphicitem.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QLineEdit* edit = new QLineEdit(this);
    auto *delayUtil = new DelayWidgetController(edit, &QLineEdit::textChanged, edit);

    connect(delayUtil, SIGNAL(requestDelay()), this, SLOT(checkSlot()));

    setCentralWidget(edit);

    QList<GraphItem*> items;

    auto cube = new GraphItem(ItemType::Cube);
    items.append(cube);

    auto rect =  new GraphItem(ItemType::Rectangle);
    items.append(rect);

    bool hasCubeOrTriangle = FinderItem::findItem(items,ItemType::Triangle);

    qInfo() << "HasCube : " << hasCubeOrTriangle;

    bool hasAllExceptRect = FinderItem::findItem(items, ItemType::AllType & ~ItemTypes(ItemType::Rectangle));

    qInfo() << "hasAll without rectangle : " << hasAllExceptRect;
}


void MainWindow::checkSlot() {
    qInfo() << "CheckSlot CheckSlot";
}