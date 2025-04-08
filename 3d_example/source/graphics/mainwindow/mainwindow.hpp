#ifndef adsja8932dij4221
#define adsja8932dij4221

#include <QMainWindow>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void checkSlot();
};

#endif