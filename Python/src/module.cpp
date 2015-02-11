#include <GameRoot.h>
#include <RobotCommand.h>
#include <VisionFrame.h>
#include <PythonVisionFrame.h>
#include <RefereeCommand.h>
#include <PythonRefereeCommand.h>
#include <Pose.h>
#include <Position.h>
#include <boost/python.hpp>
#include <iostream>

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand);

void sendCommand(std::shared_ptr<Rule::RobotCommand> robotCommand){
            Rule::GameRoot::getSingleton().addRobotCommand(robotCommand);
}

//Creates the rule_python module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;

    def("sendCommand", &sendCommand, "Send a RobotCommand to the engine");

    //RobotCommand
    class_<RobotCommand, std::shared_ptr<RobotCommand>>("RobotCommand", init<>())
            .def_readwrite("isTeamYellow", &RobotCommand::isTeamYellow)
	    .def_readwrite("dribble", &RobotCommand::dribble)
	    .def_readwrite("dribbleSpeed", &RobotCommand::dribbleSpeed)
	    .def_readwrite("kick", &RobotCommand::kick)
	    .def_readwrite("kickSpeed", &RobotCommand::kickSpeed)
	    .def_readwrite("robotId", &RobotCommand::robotId)
	    .def_readwrite("stop", &RobotCommand::stop)
	    .def_readwrite("pose", &RobotCommand::pose);
   
    //Pose
    class_<Pose, std::shared_ptr<Pose>>("Pose")
	    .def_readwrite("coord", &Pose::coord, "C'est la coordonée, dumbass")
	    .def_readwrite("orientation", &Pose::orientation, "C'est l'orientation, dumbass");

    //Position
    class_<Position, std::shared_ptr<Position>>("Position")
	    .def_readwrite("x", &Position::x)
	    .def_readwrite("y", &Position::y)
	    .def_readwrite("z", &Position::z);

    //VisionFrame
    {
    scope vision_frame =
    class_<PythonVisionFrame>("VisionFrame", no_init)
	    .def_readonly("cameraId", &PythonVisionFrame::cameraId)
	    .def_readonly("frameId", &PythonVisionFrame::frameId)
	    .def_readonly("teamCount", &PythonVisionFrame::teamCount)
	    .def_readonly("balls", &PythonVisionFrame::balls)
	    .def_readonly("teams", &PythonVisionFrame::teams);
    
    class_<VisionFrame::Ball>("Ball", no_init) //Should this be in it's own namespace?
    	    .def_readonly("position", &VisionFrame::Ball::position);

    class_<VisionFrame::Team::Robot>("Robot", no_init) //Should this be in it's own namespace?
	    .def_readonly("robotId", &VisionFrame::Team::Robot::robotId) 
	    .def_readonly("pose", &VisionFrame::Team::Robot::pose);

    class_<PythonVisionFrame::Team>("Team", no_init)
            .def_readonly("teamId", &PythonVisionFrame::Team::teamId)
            .def_readonly("robots", &PythonVisionFrame::Team::robots)
            .def_readonly("robotCount", &PythonVisionFrame::Team::robotCount);
    }

    //RefereeCommand
    {
    scope referee_command =
    class_<PythonRefereeCommand>("RefereeCommand", no_init)
	    .def_readonly("command" , &PythonRefereeCommand::command)
	    .def_readonly("packetTimeStamp" , &PythonRefereeCommand::packetTimeStamp)
	    .def_readonly("stage" , &PythonRefereeCommand::stage)
	    .def_readonly("teams" , &PythonRefereeCommand::teams)
	    .def_readonly("teamCount" , &PythonRefereeCommand::teamCount);
    
    class_<PythonRefereeCommand::Team>("Team", no_init)
	    .def_readonly("goalieCount" , &PythonRefereeCommand::Team::goalieCount)
	    .def_readonly("name" , &PythonRefereeCommand::Team::name)
	    .def_readonly("redCardsCount" , &PythonRefereeCommand::Team::redCardsCount)
	    .def_readonly("timeoutsLeft" , &PythonRefereeCommand::Team::timeoutsLeft)
	    .def_readonly("timeoutTime" , &PythonRefereeCommand::Team::timeoutTime)
	    .def_readonly("yellowCardsCount" , &PythonRefereeCommand::Team::yellowCardsCount)
	    .def_readonly("yellowCardsRemainingTime" , &PythonRefereeCommand::Team::yellowCardsRemainingTime)
	    .def_readonly("yellowCardsRemainingTimeCount" , &PythonRefereeCommand::Team::yellowCardsRemainingTimeCount);

    class_<RefereeCommand::Stage>("Stage", no_init) //Should this be in it's own namespace?
	    .def_readonly("name" , &RefereeCommand::Stage::name)
	    .def_readonly("timeLeft" , &RefereeCommand::Stage::timeLeft);

    class_<RefereeCommand::Command>("Command", no_init) //Should this be in it's own namespace?
	    .def_readonly("name" , &RefereeCommand::Command::name)
	    .def_readonly("timeStamp" , &RefereeCommand::Command::timeStamp);
    }

}



