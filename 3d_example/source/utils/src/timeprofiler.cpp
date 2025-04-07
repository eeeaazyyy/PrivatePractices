#include <QDebug>

#include "timeprofiler.hpp"

namespace utils {

// Инициализация статических членов
QMutex TimeProfiler::lock_;
int TimeProfiler::indent_ = 0;
bool TimeProfiler::enabled_ = true;

TimeProfiler::TimeProfiler(const QString &name, bool autoLog)
        : name_(name), autoLog_(autoLog) {
    QMutexLocker locker(&lock_);

    timer_.start();
    ++indent_;
}

TimeProfiler::~TimeProfiler() {
    // if(autoLog_) {
    //     log();
    // }
    QMutexLocker locker(&lock_);
    --indent_;
}

double TimeProfiler::elapsed() const {
    return static_cast<double>(timer_.nsecsElapsed()) / 1000000;
}

void TimeProfiler::log() const {
    QMutexLocker locker(&lock_);
    qInfo() << formatMessage();
}

void TimeProfiler::setEnabled(bool enabled) {
    enabled_ = enabled;
}

QString TimeProfiler::formatMessage() const {
    return QString("%1%2(): %3 ms")
            .arg(QString(indent_ * 2, ' '))  // Отступ для вложенных вызовов
            .arg(name_)
            .arg(timer_.elapsed());
}

} // namespace utils

// Макросы для удобного использования
#define PROFILE_FUNCTION() utils::TimeProfiler __profiler__(Q_FUNC_INFO)
#define PROFILE_SCOPE(name) utils::TimeProfiler __profiler__(name)
#define PROFILE_START(name) auto __profiler_##name = std::make_unique<utils::TimeProfiler>(name, false)
#define PROFILE_STOP(name) do { __profiler_##name->log(); __profiler_##name.reset(); } while(0)