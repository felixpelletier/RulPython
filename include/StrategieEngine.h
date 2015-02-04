#ifndef __StrategieEngine_H_
#define __StrategieEngine_H_

#include <boost/python.hpp>
#include <thread>
#include <RuleSSL/VisionListener.h>
#include <RuleSSL/RefereeListener.h>
#include <RuleSSL/ThreadSafeCircularBuffer.h>

using namespace boost::python;


class StrategieEngine: public Rule::VisionListener, public Rule::RefereeListener {
public:
    StrategieEngine(int buffersLength=20);
    ~StrategieEngine();

    virtual void refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> newRefereeCommand) override;
    virtual void visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> newVisionFrames) override;

    void initPythonInterpreter();
    void launch();
    void terminate();
    void updatePosition();

private:
    std::thread updateThread;
    Streams::ThreadSafeCircularBuffer<std::shared_ptr<Rule::VisionFrame>> visionFrames;
    template<class T> list vectorToPython(const std::vector<T>& v);
    bool threadTerminated = false;

};

#endif //__StrategieEngine_H_
