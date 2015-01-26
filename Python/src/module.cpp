#include <GameRoot.h>
#include <RobotCommand.h>
#include <Pose.h>
#include <Position.h>
#include <boost/python.hpp>

void sendCommand(Rule::RobotCommand robotCommand);

void sendCommand(Rule::RobotCommand robotCommand){
            std::shared_ptr<Rule::RobotCommand> robotCommand_p = std::make_shared<Rule::RobotCommand>(robotCommand);
            Rule::GameRoot::getSingleton().addRobotCommand(robotCommand_p);
}

//Creates the POC module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;

    def("sendCommand", &sendCommand);

    class_<RobotCommand>("RobotCommand")
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

