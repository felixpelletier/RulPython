#ifndef __BaseApplication_H_
#define __BaseApplication_H_

#include <VisionListener.h>
#include <RefereeListener.h>

#include <boost/asio/io_service.hpp>

class BaseApplication {
public:
    BaseApplication();
    virtual ~BaseApplication();
    virtual void run();
protected:
    virtual void initialize();

    virtual void createPlugins();
    virtual void createListeners() = 0;
    virtual void createGame() = 0;
private:
    boost::asio::io_service *io_service;
};

#endif //__BaseApplication_H_
