#ifndef __RulApplication_H_
#define __RulApplication_H_

#include "BaseApplication.h"
#include <StrategieEngine.h>

class PythonApplication : public BaseApplication {
public:
    PythonApplication() {}
protected:
    virtual void createListeners() override;
    virtual void createGame() override;
    StrategieEngine strategie;
};

#endif //__RulApplication_H_
