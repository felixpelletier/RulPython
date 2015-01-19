#ifndef __BaseApplication_H_
#define __BaseApplication_H_

#include <RuleSSL/VisionListener.h>
#include <RuleSSL/RefereeListener.h>

#include <boost/asio/io_service.hpp>

class BaseApplication : public Rule::VisionListener, public Rule::RefereeListener {
public:
    BaseApplication();
    virtual ~BaseApplication();
    virtual void run();
protected:
    virtual void initialize();

    virtual void createPlugins();
    virtual void createListeners();
    virtual void createGame() = 0;
private:
    boost::asio::io_service *io_service;
};

#endif //__BaseApplication_H_