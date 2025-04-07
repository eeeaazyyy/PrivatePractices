#include <alertmodel.hpp>


class TestFile : public QObject {
public:
    TestFile() : QObject() {
        AlertModel* alertModel = new AlertModel(this);



        

    };

    ~TestFile() override = default;
};