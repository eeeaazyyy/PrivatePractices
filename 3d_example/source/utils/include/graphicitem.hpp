#ifndef kfosdkfo_asdaijrfjkmiad
#define kfosdkfo_asdaijrfjkmiad

#include <QList>

class GraphItem;

enum ItemType {
    Cube        = 0x01,
    Triangle    = 0x02,
    Rectangle   = 0x04,
    AllType     = Cube | Triangle | Rectangle,
};
Q_DECLARE_FLAGS(ItemTypes, ItemType)

class FinderItem {
public:
    FinderItem() = default;
    ~FinderItem() = default;

    static bool findItem(const QList<GraphItem*> &items, ItemTypes types);
};

class GraphItem {
public:
    explicit GraphItem(ItemType type);
    ~GraphItem() = default;

    ItemType type() const;
    void setType(ItemType type);

private:
    ItemType type_;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ItemTypes)
#endif // kfosdkfo_asdaijrfjkmiad