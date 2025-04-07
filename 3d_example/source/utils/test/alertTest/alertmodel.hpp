#ifndef ofdsojsgmdnbprrwpasdastgsd
#define ofdsojsgmdnbprrwpasdastgsd

#include <QObject>
#include <QSet>
#include <QHash>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>

class AlertsController;
class AlertGenerator;
class AlertClass;
class Alert;

/*
 * 
 * Item
 */

class Item {
public:
    explicit Item(const QList<QUuid>& classId);
    ~Item() = default;

    QList<QUuid> id() const;

private:
    QList<QUuid> id_;
};


/*
 * 
 * AlertModel
 */

class AlertModel : public QObject {
Q_OBJECT
public:
    AlertModel(QObject* parent);
    ~AlertModel() override;

public:
    bool hashContain(const QSet<QUuid> alertsClass);
    bool multiHashContain(const QList<QUuid> alertsClass);

signals:
    void checkedItems();
    void checkItemsFinished();

public slots:
    void addAlerts();
    void removeAlerts();

    void addAlertsToContainer(const QList<QUuid> &alerts);
    void removeAlertsFromContainer(const QList<QUuid> &alerts);

    void finishCheckItem();
    void checkItemTimer();

private:
    void start();

    void setAlertController(const QSharedPointer<AlertsController> &controller);
    void setGenerator();

    void generateItems();
    void checkItems();

private:
    QThread* thread_;
    AlertGenerator* generator_;
    QSharedPointer<AlertsController> controller_;
    QTimer* timer_;

    QList<AlertClass> alertClasses_;
    QList<Item> items_;

    QHash<QUuid, Alert> alerts_;
    QMultiHash<QUuid, Alert> alertsByClass_;

    double timeHash_;
    double timeMultiHash_;
};

#endif