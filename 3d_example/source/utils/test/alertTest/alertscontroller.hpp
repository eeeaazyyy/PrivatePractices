#include <QObject>
#include <QTimer>

#include <QSharedPointer>

class AlertsController : public QObject {
Q_OBJECT
public:
    AlertsController(QObject* parent);
    ~AlertsController() override = default;

private slots:
    void handleGenerate();
    void handleRemove();

signals:
    void generateAlerts();
    void removeAlerts();

private:
    QTimer* timer_;
    QTimer* timerRemove_;
};