#include <boost/python.hpp>
#include <thread>

using namespace boost::python;

class StrategieEngine {
public:
    StrategieEngine();
    ~StrategieEngine();

    void updatePosition();

private:
    std::thread updateThread;
    template<class T> list vectorToPython(const std::vector<T>& v);
    bool threadTerminated = false;

};

