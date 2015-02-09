#ifndef __PythonRefereeCommand_H_
#define __PythonRefereeCommand_H_

#include <stdint.h>
#include <memory>
#include <RefereeCommand.h>
#include <boost/python.hpp>

namespace Rule {

typedef uint32_t uint32;

struct PythonRefereeCommand
{
	
	PythonRefereeCommand( const RefereeCommand& refereeCommand ){
		this->command = refereeCommand.command;
		this->teamCount = refereeCommand.teamCount;
		this->packetTimeStamp = refereeCommand.packetTimeStamp;
		this->stage = refereeCommand.stage;
		for (int t = 0; t < refereeCommand.teamCount; t++){
			Team team = Team(refereeCommand.teams[t]);
			this->teams.append(team);
		}
	}

	struct Team {
		Team( const RefereeCommand::Team& other ) {
			this->goalieCount = other.goalieCount;
			this->name = other.name;
			this->redCardsCount = other.redCardsCount;
			this->score = other.score;
			this->timeoutsLeft = other.timeoutsLeft;
			this->timeoutTime = other.timeoutTime;
			this->yellowCardsCount = other.yellowCardsCount;
			this->yellowCardsRemainingTimeCount = other.yellowCardsRemainingTimeCount;
			for (int y = 0; y < other.yellowCardsRemainingTimeCount; y++){
				this->yellowCardsRemainingTime.append(other.yellowCardsRemainingTime[y]);
			}

		}

		uint32 goalieCount;
		std::string name;
		uint32 redCardsCount;
		uint32 score;
		uint32 timeoutsLeft;
		uint32 timeoutTime;
		uint32 yellowCardsCount;
		boost::python::list yellowCardsRemainingTime;
		int yellowCardsRemainingTimeCount;
	};

    RefereeCommand::Command command;
    uint64 packetTimeStamp;
    RefereeCommand::Stage stage;
    boost::python::list teams;
    uint32 teamCount;	
};



} //namespace Rule

#endif //__PythonRefereeCommand_H_
