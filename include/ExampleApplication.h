#ifndef __RulApplication_H_
#define __RulApplication_H_

#include "BaseApplication.h"

class ExampleApplication : public BaseApplication {
public:
    virtual void refereeCommandRetrieved(Rule::RefereeCommand refereeCommand) override;
    virtual void visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> visionFrames) override;
protected:
    virtual void createGame() override;
};

#endif //__RulApplication_H_