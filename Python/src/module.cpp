#include <GameRoot.h>
#include <RobotCommand.h>
#include <Pose.h>
#include <Position.h>
#include <boost/python.hpp>
#include <iostream>

std::shared_ptr<Rule::RobotCommand> statement;

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand);

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand){
            Rule::GameRoot::getSingleton().addRobotCommand(robotCommand);
}

std::shared_ptr<Rule::RobotCommand> getFizzy(){

	std::shared_ptr<Rule::RobotCommand> fizzy = std::make_shared<Rule::RobotCommand>();

	fizzy->isTeamYellow = true;
	fizzy->dribble = true;
	fizzy->dribbleSpeed = 1;
	fizzy->kick = true;
	fizzy->kickSpeed = 2;
	fizzy->robotId = 1;
	fizzy->stop = false;
	fizzy->pose.coord.x = 342;
	fizzy->pose.coord.y = rand() % 2;
	fizzy->pose.orientation = 5;

	statement = fizzy;

	return fizzy;
}

std::shared_ptr<Rule::RobotCommand> getStatement(){

	return statement;
}

//Creates the POC module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;

    def("sendCommand", &sendCommand);

    class_<RobotCommand, std::shared_ptr<RobotCommand>>("RobotCommand", init<>())
            .def_readwrite("isTeamYellow", &RobotCommand::isTeamYellow)
	    .def_readwrite("dribble", &RobotCommand::dribble)
	    .def_readwrite("dribbleSpeed", &RobotCommand::dribbleSpeed)
	    .def_readwrite("kick", &RobotCommand::kick)
	    .def_readwrite("kickSpeed", &RobotCommand::kickSpeed)
	    .def_readwrite("robotId", &RobotCommand::robotId)
	    .def_readwrite("stop", &RobotCommand::stop)
	    .def_readwrite("pose", &RobotCommand::pose);
    
    class_<Pose>("Pose")
	    .def_readwrite("coord", &Pose::coord)
	    .def_readwrite("orientation", &Pose::orientation);

    class_<Position>("Position")
	    .def_readwrite("x", &Position::x)
	    .def_readwrite("y", &Position::y)
	    .def_readwrite("z", &Position::z);

}

