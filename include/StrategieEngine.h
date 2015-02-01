#include <boost/python.hpp>
#include <thread>

class StrategieEngine {
public:
    StrategieEngine();
    ~StrategieEngine();

    void updatePosition();

private:
    std::thread updateThread;
    bool threadTerminated = false;

};

