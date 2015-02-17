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

class PythonRobotCommand : public Rule::RobotCommand{

	private:
		Rule::VisionFrame::Team::Robot robot;	
	public:
		PythonRobotCommand(Rule::VisionFrame::Team::Robot robot){
			this->robotId = robot.robotId;
			this->robot = robot;
		}
};

void sendCommand(PythonRobotCommand robotCommand);

void sendCommand(PythonRobotCommand robotCommand){
            Rule::GameRoot::getSingleton().addRobotCommand(std::make_shared<Rule::RobotCommand>(robotCommand));
}

Rule::PythonVisionFrame getFrame(){
	Rule::VisionFrame frame;
	frame.cameraId = 42;
	Rule::PythonVisionFrame pframe = Rule::PythonVisionFrame(frame);
	return pframe;
}

//Creates the rule_python module in python containing various utilities (PLUGINS)
BOOST_PYTHON_MODULE(rule_python)
{
    using namespace boost::python;
    using namespace Rule;

    def("sendCommand", &sendCommand);
    def("getFrame", &getFrame);

    //RobotCommand
    class_<PythonRobotCommand>("RobotCommand", init<VisionFrame::Team::Robot>())
            .def_readwrite("isTeamYellow", &PythonRobotCommand::isTeamYellow)
	    .def_readwrite("dribble", &PythonRobotCommand::dribble)
	    .def_readwrite("dribbleSpeed", &PythonRobotCommand::dribbleSpeed)
	    .def_readwrite("kick", &PythonRobotCommand::kick)
	    .def_readwrite("kickSpeed", &PythonRobotCommand::kickSpeed)
	    .def_readwrite("stop", &PythonRobotCommand::stop)
	    .def_readwrite("pose", &PythonRobotCommand::pose);
   
    //Pose
    class_<Pose, std::shared_ptr<Pose>>("Pose")
	    .def_readwrite("coord", &Pose::coord)
	    .def_readwrite("orientation", &Pose::orientation);

    //Position
    class_<Position, std::shared_ptr<Position>>("Position")
	    .def_readwrite("x", &Position::x)
	    .def_readwrite("y", &Position::y)
	    .def_readwrite("z", &Position::z);

    //VisionFrame
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

    class_<PythonVisionFrame::Team>("VisionFrame.Team", no_init)
            .def_readonly("teamId", &PythonVisionFrame::Team::teamId)
            .def_readonly("robots", &PythonVisionFrame::Team::robots)
            .def_readonly("robotCount", &PythonVisionFrame::Team::robotCount);

    //RefereeCommand
    class_<PythonRefereeCommand>("RefereeCommand", no_init)
	    .def_readonly("command" , &PythonRefereeCommand::command)
	    .def_readonly("packetTimeStamp" , &PythonRefereeCommand::packetTimeStamp)
	    .def_readonly("stage" , &PythonRefereeCommand::stage)
	    .def_readonly("teams" , &PythonRefereeCommand::teams)
	    .def_readonly("teamCount" , &PythonRefereeCommand::teamCount);
    
    class_<PythonRefereeCommand::Team>("RefereeCommand.Team", no_init)
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



