#ifndef __StrategieEngine_H_
#define __StrategieEngine_H_

#include <boost/python.hpp>
#include <thread>
#include <RuleSSL/VisionListener.h>
#include <RuleSSL/RefereeListener.h>

using namespace boost::python;


class StrategieEngine: public Rule::VisionListener, public Rule::RefereeListener {
public:
    StrategieEngine();
    ~StrategieEngine();

    virtual void refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> refereeCommand) override;
    virtual void visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> visionFrames) override;

    void initPythonInterpreter();
    void launch();
    void terminate();
    void updatePosition();

private:
    std::thread updateThread;
    template<class T> list vectorToPython(const std::vector<T>& v);
    bool threadTerminated = false;

};

#endif //__StrategieEngine_H_
