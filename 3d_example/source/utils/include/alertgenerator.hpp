#ifndef alertGeneratorUtils__fsdafnriwbad
#define alertGeneratorUtils__fsdafnriwbad

#include <QObject>
#include <QUuid>
#include <QMutex>

class AlertGenerator : public QObject {
Q_OBJECT
public:
    AlertGenerator(const QUuid &id);
    ~AlertGenerator() override = default;

    QUuid id() const;

public slots:
    void generateAlerts();
    void removeAlerts();

signals:
    void alertsGenerated(const QList<QUuid> &alerts);
    void alertsRemoved(const QList<QUuid> &alerts);

private:
    QUuid id_;

    QList<QUuid> alerts_;

    mutable QMutex lock_;
};

#endif 