#include <QRandomGenerator>
#include <QDebug>

#include "alertgenerator.hpp"

#define DEFAULT_SIZE_TEST_ALERT (int) 10000

AlertGenerator::AlertGenerator(const QUuid &id)
        : QObject(), id_(id), alerts_({}) {
}

QUuid AlertGenerator::id() const {
    return id_;
}

void AlertGenerator::generateAlerts() {
    qInfo() << "AlertGenerator::generateAlerts";
    QMutexLocker locker(&lock_);

    QList<QUuid> addAlert;
    addAlert.reserve(DEFAULT_SIZE_TEST_ALERT);

    for (int i = 0; i < DEFAULT_SIZE_TEST_ALERT; i++) {
        addAlert.append(QUuid::createUuid());
    }

    alerts_.append(addAlert);
    
    locker.unlock();

    Q_EMIT alertsGenerated(addAlert);
}

void AlertGenerator::removeAlerts() {
    qInfo() << "AlertGenerator::removeAlerts";
    QMutexLocker locker(&lock_);

    QList<QUuid> removeAlert;
    if (alerts_.size() < 2) { 
        qInfo() << "AlertGenerator::alerts_.size() < 2";
        return; }
    removeAlert.reserve(alerts_.size() / 2);

    qInfo() << "AlertGenerator::removeAlerts :: size";
    int size = QRandomGenerator::global()->bounded(1, alerts_.size() - 1);

    for (int i = 1; i < size; i++) {
        //qInfo() << "AlertGenerator::removeAlerts :: index";
        int index = QRandomGenerator::global()->bounded(i, alerts_.size() - 1);
        removeAlert.append(alerts_.at(index));
    }

    for (const auto& alert : removeAlert) {
        alerts_.removeAll(alert);
    }
    locker.unlock();

    Q_EMIT alertsRemoved(removeAlert);

}
