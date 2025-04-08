#include <graphicseditor.hpp>

#include "QLineEdit"

#include "mainwindow.hpp"

#include "include/delaywidgetcontroller.hpp"
#include "test/alertTest/alertmodel.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QLineEdit* edit = new QLineEdit(this);
    auto *delayUtil = new DelayWidgetController(edit, &QLineEdit::textChanged, edit);

    connect(delayUtil, SIGNAL(requestDelay()), this, SLOT(checkSlot()));

    setCentralWidget(edit);
}


void MainWindow::checkSlot() {
    qInfo() << "CheckSlot CheckSlot";
}