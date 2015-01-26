#ifndef __RulApplication_H_
#define __RulApplication_H_

#include "BaseApplication.h"
#include <StrategieEngine.h>

class ExampleApplication : public BaseApplication {
	StrategieEngine strategie;
public:
    virtual void refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> refereeCommand) override;
    virtual void visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> visionFrames) override;
protected:
    virtual void createGame() override;
};

#endif //__RulApplication_H_
