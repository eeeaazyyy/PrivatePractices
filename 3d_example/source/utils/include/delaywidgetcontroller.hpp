#ifndef delayutilwidget_dufhyhfjkafyry
#define delayutilwidget_dufhyhfjkafyry

#include <QObject>
#include <QTimer>

class DelayWidgetController : public QObject {
Q_OBJECT
public:
    template<typename Widget, typename Signal>
    explicit DelayWidgetController(Widget* widget, Signal signal, QObject* parent = nullptr)
        : QObject(parent), timer_(new QTimer(this)), delay_(500) 
    {
        connect(widget, signal, this, &DelayWidgetController::processSignalWidget);
        activateTimer();
    }

public:
    void setDelayTime(int delay);

signals:
    void requestDelay();

private:
    void activateTimer();

private slots:
    void processSignalWidget();

private:
    QTimer* timer_;
    int delay_;

};

#endif


