#include <graphicseditor.hpp>

#include "mainwindow.hpp"

#include "test/alertTest/alertmodel.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    //auto* editor = new GraphicsEditor;
    
    AlertModel* model = new AlertModel(this);

    //setCentralWidget(editor);
}