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

    def("send_command", &sendCommand, "Send a robot_command to the engine");

    //RobotCommand
    class_<RobotCommand, std::shared_ptr<RobotCommand>>("robot_command", init<>())
            .def_readwrite("is_team_yellow", &RobotCommand::isTeamYellow)
	    .def_readwrite("dribble", &RobotCommand::dribble)
	    .def_readwrite("dribble_speed", &RobotCommand::dribbleSpeed)
	    .def_readwrite("kick", &RobotCommand::kick)
	    .def_readwrite("kick_speed", &RobotCommand::kickSpeed)
	    .def_readwrite("robot_id", &RobotCommand::robotId)
	    .def_readwrite("stop", &RobotCommand::stop)
	    .def_readwrite("pose", &RobotCommand::pose);
   
    //Pose
    class_<Pose, std::shared_ptr<Pose>>("pose")
	    .def_readwrite("coord", &Pose::coord, "C'est la coordonée, dumbass")
	    .def_readwrite("orientation", &Pose::orientation, "C'est l'orientation, dumbass");

    //Position
    class_<Position, std::shared_ptr<Position>>("position")
	    .def_readwrite("x", &Position::x)
	    .def_readwrite("y", &Position::y)
	    .def_readwrite("z", &Position::z);

    //VisionFrame
    {
    scope vision_frame =
    class_<PythonVisionFrame>("vision_frame", no_init)
	    .def_readonly("camera_id", &PythonVisionFrame::cameraId)
	    .def_readonly("frame_id", &PythonVisionFrame::frameId)
	    .def_readonly("balls", &PythonVisionFrame::balls)
	    .def_readonly("teams", &PythonVisionFrame::teams);
    
    class_<VisionFrame::Ball>("ball", no_init) //Should this be in it's own namespace?
    	    .def_readonly("position", &VisionFrame::Ball::position);

    class_<VisionFrame::Team::Robot>("robot", no_init) //Should this be in it's own namespace?
	    .def_readonly("robot_id", &VisionFrame::Team::Robot::robotId) 
	    .def_readonly("pose", &VisionFrame::Team::Robot::pose);

    class_<PythonVisionFrame::Team>("team", no_init)
            .def_readonly("team_id", &PythonVisionFrame::Team::teamId)
            .def_readonly("robots", &PythonVisionFrame::Team::robots);
    }

    //RefereeCommand
    {
    scope referee_command =
    class_<PythonRefereeCommand>("referee_command", no_init)
	    .def_readonly("command" , &PythonRefereeCommand::command)
	    .def_readonly("packet_time_stamp" , &PythonRefereeCommand::packetTimeStamp)
	    .def_readonly("stage" , &PythonRefereeCommand::stage)
	    .def_readonly("teams" , &PythonRefereeCommand::teams);
    
    class_<PythonRefereeCommand::Team>("team", no_init)
	    .def_readonly("goalie_count" , &PythonRefereeCommand::Team::goalieCount)
	    .def_readonly("name" , &PythonRefereeCommand::Team::name)
	    .def_readonly("red_cards_count" , &PythonRefereeCommand::Team::redCardsCount)
	    .def_readonly("timeouts_left" , &PythonRefereeCommand::Team::timeoutsLeft)
	    .def_readonly("timeout_time" , &PythonRefereeCommand::Team::timeoutTime)
	    .def_readonly("yellow_cards_count" , &PythonRefereeCommand::Team::yellowCardsCount)
	    .def_readonly("yellow_cards_remaining_time" , &PythonRefereeCommand::Team::yellowCardsRemainingTime);

    class_<RefereeCommand::Stage>("stage", no_init)
	    .def_readonly("name" , &RefereeCommand::Stage::name)
	    .def_readonly("time_left" , &RefereeCommand::Stage::timeLeft);

    class_<RefereeCommand::Command>("command", no_init)
	    .def_readonly("name" , &RefereeCommand::Command::name)
	    .def_readonly("time_stamp" , &RefereeCommand::Command::timeStamp);
    }

}



