#ifndef TimeProfilerUtils_1kbfjh34u
#define TimeProfilerUtils_1kbfjh34u

#include <QElapsedTimer>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

namespace utils {

class TimeProfiler {
public:
    explicit TimeProfiler(const QString& name, bool autoLog = true);
    ~TimeProfiler();

    double elapsed() const;
    void log() const;

    static void setEnabled(bool enabled);

private:
    QString formatMessage() const;

private:
    QElapsedTimer timer_;
    QString name_;
    bool autoLog_;

     static QMutex lock_;
     static int indent_;
     static bool enabled_;
};




}
#endif