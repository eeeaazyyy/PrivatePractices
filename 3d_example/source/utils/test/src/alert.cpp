#include "alert.hpp"

/*
 * AlertClass
 *
 */

AlertClass::AlertClass(const QUuid &id, const TypeAlertClass type)
        : id_(id), type_(type) {
}

QUuid AlertClass::id() const {
    return id_;
}

TypeAlertClass AlertClass::type() const {
    return type_;
}


/*
 * Alert
 *
 */

Alert::Alert(const QUuid &id, const QUuid &alertClassId, const TypeAlert type)
        : id_(id), alertClassId_(alertClassId), type_(type) {
}

bool Alert::operator==(const Alert &other) const {
    return id_ == other.id();
}

QUuid Alert::id() const {
    return id_;
}

QUuid Alert::alertClassId() const {
    return alertClassId_;
}

TypeAlert Alert::type() const {
    return type_;
}
