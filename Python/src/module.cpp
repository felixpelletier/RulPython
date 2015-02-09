#include <GameRoot.h>
#include <RobotCommand.h>
#include <VisionFrame.h>
#include <PythonVisionFrame.h>
#include <Pose.h>
#include <Position.h>
#include <boost/python.hpp>
#include <iostream>

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand);

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand){
            Rule::GameRoot::getSingleton().addRobotCommand(robotCommand);
}

Rule::PythonVisionFrame getFrame(){
	Rule::VisionFrame frame;
	frame.cameraId = 42;
	Rule::PythonVisionFrame pframe = Rule::PythonVisionFrame(frame);
	return pframe;
}

//Creates the POC module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;

    def("sendCommand", &sendCommand);
    def("getFrame", &getFrame);

    class_<RobotCommand, std::shared_ptr<RobotCommand>>("RobotCommand", init<>())
            .def_readwrite("isTeamYellow", &RobotCommand::isTeamYellow)
	    .def_readwrite("dribble", &RobotCommand::dribble)
	    .def_readwrite("dribbleSpeed", &RobotCommand::dribbleSpeed)
	    .def_readwrite("kick", &RobotCommand::kick)
	    .def_readwrite("kickSpeed", &RobotCommand::kickSpeed)
	    .def_readwrite("robotId", &RobotCommand::robotId)
	    .def_readwrite("stop", &RobotCommand::stop)
	    .def_readwrite("pose", &RobotCommand::pose);
    
    class_<Pose, std::shared_ptr<Pose>>("Pose")
	    .def_readwrite("coord", &Pose::coord)
	    .def_readwrite("orientation", &Pose::orientation);

    class_<Position, std::shared_ptr<Position>>("Position")
	    .def_readwrite("x", &Position::x)
	    .def_readwrite("y", &Position::y)
	    .def_readwrite("z", &Position::z);

    class_<PythonVisionFrame>("VisionFrame", no_init)
	    .def_readonly("cameraId", &PythonVisionFrame::cameraId)
	    .def_readonly("frameId", &PythonVisionFrame::frameId)
	    .def_readonly("teamCount", &PythonVisionFrame::teamCount)
	    .def_readonly("balls", &PythonVisionFrame::balls)
	    .def_readonly("teams", &PythonVisionFrame::teams);
    
    class_<VisionFrame::Ball>("Ball", no_init)
    	    .def_readonly("position", &VisionFrame::Ball::position);

    class_<VisionFrame::Team::Robot>("Robot", no_init)
	    .def_readonly("robotId", &VisionFrame::Team::Robot::robotId) 
	    .def_readonly("pose", &VisionFrame::Team::Robot::pose);

    class_<PythonVisionFrame::Team>("Team", no_init)
            .def_readonly("teamId", &PythonVisionFrame::Team::teamId)
            .def_readonly("robots", &PythonVisionFrame::Team::robots)
            .def_readonly("robotCount", &PythonVisionFrame::Team::robotCount);

}



