#ifndef fsfipknuuefafigosensnf
#define fsfipknuuefafigosensnf

#include <QUuid>

enum class TypeAlert {
    typeConfirmed = 0, typeOperationState, typeCritical, typeError
};
enum class TypeAlertClass {
    type1 = 0, type2, type3, type4
};

class AlertClass {
public:
    explicit AlertClass(const QUuid& id, const TypeAlertClass type);
    ~AlertClass() = default;

public:
    QUuid id() const;
    TypeAlertClass type() const;

private:
    QUuid id_;
    TypeAlertClass type_;
};


class Alert {
public:
    Alert() = default;
    explicit Alert(const QUuid& id, const QUuid &alertClassId, const TypeAlert type);
    ~Alert() = default;

public:
    bool operator==(const Alert& other) const;

    QUuid id() const;
    QUuid alertClassId() const;

    TypeAlert type() const;

private:
    QUuid id_;
    QUuid alertClassId_;

    TypeAlert type_;
};

#endif