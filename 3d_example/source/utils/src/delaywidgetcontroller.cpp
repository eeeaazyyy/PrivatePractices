#include "delaywidgetcontroller.hpp"

#define TIMER_DEFAULT_DELAY (int)500

void DelayWidgetController::setDelayTime(int delay) {
    delay_ = delay;
}

void DelayWidgetController::activateTimer() {
    timer_->setInterval((delay_ > 0) ? delay_ : TIMER_DEFAULT_DELAY);
    timer_->setSingleShot(true);

    if (timer_->isActive()) { timer_->stop(); }
    timer_->start(delay_);

    connect(timer_, &QTimer::timeout, [this](){
        Q_EMIT requestDelay();
    });
}

void DelayWidgetController::processSignalWidget() {
    if (timer_->isActive()) { timer_->stop(); }

    timer_->start(delay_);
}