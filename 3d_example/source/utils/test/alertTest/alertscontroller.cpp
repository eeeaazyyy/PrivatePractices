#include <QTimerEvent>
#include <QDebug>

#include <alertgenerator.hpp>

#include "alertscontroller.hpp"

#define DEFAULT_TIMER_VALUE_FOR_APPEND (int) 5000
#define DEFAULT_TIMER_VALUE_FOR_REMOVE (int) 4800

/*
 * 
 * AlertsController
 */

AlertsController::AlertsController(QObject* parent)
    : QObject(parent), timer_(nullptr), timerRemove_(nullptr) {

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &AlertsController::handleGenerate);
    timer_->start(DEFAULT_TIMER_VALUE_FOR_APPEND);

    timerRemove_ = new QTimer(this);
    connect(timerRemove_, &QTimer::timeout, this, &AlertsController::handleRemove);
    timerRemove_->start(DEFAULT_TIMER_VALUE_FOR_REMOVE);
}

void AlertsController::handleGenerate() {
    Q_EMIT generateAlerts();
}

void AlertsController::handleRemove() {
    Q_EMIT removeAlerts();
}