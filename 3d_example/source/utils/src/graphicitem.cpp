#include "graphicitem.hpp"

bool FinderItem::findItem(const QList<GraphItem *> &items, ItemTypes types) {
    for (const auto &item : items) {
        if (item->type() & types) { return true; }
    }

    return false;
}

/*
* GraphItem
*
* */

GraphItem::GraphItem(ItemType type)
        : type_(type) {
}

ItemType GraphItem::type() const {
    return type_;
}

void GraphItem::setType(ItemType type) {
    type_ = type;
}
