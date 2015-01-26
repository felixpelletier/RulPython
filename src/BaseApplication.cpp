#include "BaseApplication.h"

#include <GameRoot.h>
#include <VisionPlugin.h>
#include <RefereePlugin.h>
#include <UDPNavigatorPlugin.h>
#include <UDPInputStream.h>
#include <RobotCommand.h>
#include <iostream>

BaseApplication::BaseApplication() {
    this->io_service = new boost::asio::io_service;
}

BaseApplication::~BaseApplication() {
    delete this->io_service;
}

void BaseApplication::initialize(){
    this->createPlugins();
    this->createListeners();
    this->createGame();

    Rule::GameRoot::getSingleton().initialize();

}

void BaseApplication::createListeners() {
    Rule::GameRoot::getSingleton().addRefereeListener(this);
    Rule::GameRoot::getSingleton().addVisionListener(this);
}

void BaseApplication::createPlugins() {
    Rule::VisionPlugin *visionPlugin = new Rule::VisionPlugin(*io_service, "224.5.23.2", 10020, "VisionPlugin");
    Rule::RefereePlugin *refereePlugin = new Rule::RefereePlugin(*io_service, "224.5.23.1", 10003, "RefereePlugin");
    Rule::UDPNavigatorPlugin *navigatorPlugin = new Rule::UDPNavigatorPlugin(*io_service, 20011, "127.0.0.1", "UDPNavigatorPlugin");

    Rule::GameRoot::getSingleton().loadPlugins(
            { visionPlugin, refereePlugin, navigatorPlugin }
    );
}

void BaseApplication::run() {
    this->initialize();

    Rule::GameRoot::getSingleton().start();
	std::cout << "lol\n";
}
