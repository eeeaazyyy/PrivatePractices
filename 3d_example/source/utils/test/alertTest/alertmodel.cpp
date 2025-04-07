#include <QDebug>
#include <QMetaObject>
#include <QSignalBlocker>
#include <QRandomGenerator>
#include <QTimerEvent>

#include <alert.hpp>
#include <timeprofiler.hpp>
#include <alertgenerator.hpp>
#include <alertscontroller.hpp>

#include "alertmodel.hpp"

#define DEFAULT_SIZE_ITEMS (int) 1000000
#define DEFAULT_VALUE_TIMER_TO_UPDATE (int) 1000

QList<AlertClass> generateAlertClasses() {
    QList<AlertClass> alertClass = {
        AlertClass(QUuid::createUuid(), TypeAlertClass::type1),
        AlertClass(QUuid::createUuid(), TypeAlertClass::type2),
        AlertClass(QUuid::createUuid(), TypeAlertClass::type3),
        AlertClass(QUuid::createUuid(), TypeAlertClass::type4),
    };

    return alertClass;
}

/*
 * Item
 * 
 */

Item::Item(const QList<QUuid> &classId)
        : id_(classId) {
}

QList<QUuid> Item::id() const {
    return id_;
}

/*
 * AlertModel
 * 
 */

AlertModel::AlertModel(QObject *parent)
        : thread_(nullptr), generator_(new AlertGenerator(QUuid::createUuid())), controller_(new AlertsController(this)),
        timer_(new QTimer(this)), alertClasses_(generateAlertClasses()),
        items_({}), alerts_({}), alertsByClass_({}), timeHash_(0), timeMultiHash_(0) {
    qInfo() << " Create Alert Model";
    setAlertController(controller_);
    start();
    generateItems();

    timer_->start(DEFAULT_VALUE_TIMER_TO_UPDATE);
    connect(timer_, &QTimer::timeout, this, &AlertModel::checkItemTimer);

    connect(this, &AlertModel::checkedItems, this, &AlertModel::checkItems, Qt::QueuedConnection);
    connect(this, &AlertModel::checkItemsFinished, this, &AlertModel::finishCheckItem, Qt::QueuedConnection);
}

AlertModel::~AlertModel() {
}

bool AlertModel::hashContain(const QSet<QUuid> alertsClass) {
    for (const auto& alert : alerts_.values()) {
        if (alertsClass.contains(alert.alertClassId())) { return true; }
    }

    return false;   
}

bool AlertModel::multiHashContain(const QList<QUuid> alertsClass) {
    for (const auto& alert : alertsClass) {
        if (!alertsByClass_.values(alert).isEmpty()) { return true; }
    }

    return false;
}

void AlertModel::addAlerts() {
    qInfo() << "AlertModel::addAlerts";
    
    QMetaObject::invokeMethod(generator_, "generateAlerts", Qt::QueuedConnection);
}

void AlertModel::removeAlerts() {
    qInfo() << "AlertModel::removeAlerts";
    QMetaObject::invokeMethod(generator_, "removeAlerts", Qt::QueuedConnection);
}

void AlertModel::addAlertsToContainer(const QList<QUuid> &alerts) {
    for (const auto& alert : alerts) {

        int indexClass = QRandomGenerator::global()->bounded(0, alertClasses_.size() - 1);
        int typeAlert = QRandomGenerator::global()->bounded(0, 3);

        Alert mAlert = Alert(QUuid::createUuid(), alertClasses_[indexClass].id(), (TypeAlert)typeAlert);

        alerts_.insert(alert, mAlert);
        alertsByClass_.insert(mAlert.alertClassId(), mAlert);
    }
}

void AlertModel::removeAlertsFromContainer(const QList<QUuid> &alerts) {
    for (const auto& alert : alerts) {
        const QUuid classId = alerts_.value(alert).alertClassId();
        alertsByClass_.remove(classId, alerts_.value(alert));
        alerts_.remove(alert);
    }
}

void AlertModel::finishCheckItem() {
    qInfo() <<"\n Check result:" << "\nHash:" << timeHash_ <<"\nMultiHash:"<<timeMultiHash_;
    qInfo()<< "Size:\n Hash: " << sizeof(alerts_) << "\nMultiHash" << sizeof(alertsByClass_);
}

void AlertModel::checkItemTimer() {
    Q_EMIT checkedItems();
}

void AlertModel::start() {
    qInfo() << "AlertModel::start";
    thread_ = new QThread(this);
    
    generator_->moveToThread(thread_);
    connect(generator_, &AlertGenerator::destroyed, thread_, &QThread::quit);
    connect(thread_, &QThread::finished, generator_, &AlertGenerator::deleteLater);

    thread_->start();
}

void AlertModel::setAlertController(const QSharedPointer<AlertsController> &controller) {
    qInfo() << "AlertModel::setAlertController";
    if (!controller) { return; }

    connect(controller.data(), &AlertsController::generateAlerts, this, &AlertModel::addAlerts);
    connect(controller.data(), &AlertsController::removeAlerts,   this, &AlertModel::removeAlerts);
}

void AlertModel::setGenerator() {
    qInfo() << "AlertModel::setGenerator";
    if (!generator_) { return; }

    connect(generator_, &AlertGenerator::alertsGenerated, this, &AlertModel::addAlertsToContainer);
    connect(generator_, &AlertGenerator::alertsRemoved, this, &AlertModel::removeAlertsFromContainer);
}

void AlertModel::generateItems() {
    qInfo() << "AlertModel::generateItems";
    items_.clear();

    QList<Item> items{};
    items.reserve(DEFAULT_SIZE_ITEMS);

    for (int i = 0; i < DEFAULT_SIZE_ITEMS; i++) {
        int randomClassId = QRandomGenerator::global()->bounded(0, 3);
        int randomClassId2 = QRandomGenerator::global()->bounded(0, 3);
        int randomClassId3 = QRandomGenerator::global()->bounded(0, 3);
        int randomClassId4 = QRandomGenerator::global()->bounded(0, 3);

        QSet<QUuid> classes{};
        classes.insert(alertClasses_[randomClassId].id());
        classes.insert(alertClasses_[randomClassId2].id());
        classes.insert(alertClasses_[randomClassId3].id());
        classes.insert(alertClasses_[randomClassId4].id());
        
        auto item = Item(classes.values());
        items.append(item);
    }

    items_ = items;
}

void AlertModel::checkItems() {
    qInfo() << "AlertModel::checkItems";
    timeHash_ = 0;
    timeMultiHash_ = 0;
    for (const auto& item : items_) {
        QSet<QUuid> ids{};

        for (const auto& id : item.id()) {
            ids.insert(id);
        }

        QList<QUuid> listId = item.id();
        {
            utils::TimeProfiler profHash("HashContain");
            hashContain(ids);
            timeHash_ += profHash.elapsed();
        }
        {
            utils::TimeProfiler profMultiHash("MultiHashContain");
            multiHashContain(listId);
            timeMultiHash_ += profMultiHash.elapsed();
        }
    }

    Q_EMIT checkItemsFinished();
}
