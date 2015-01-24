#include "ExampleApplication.h"

#include <RuleSSL/GameRoot.h>
#include <RuleSSL/RobotCommand.h>

void ExampleApplication::createGame() {
}

void ExampleApplication::refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> refereeCommand) {
}

void ExampleApplication::visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> visionFrames) {
    int teamCount = visionFrames.front()->teamCount;
    for (int i = 0; i < teamCount; ++i) {
        int robotCount = visionFrames.front()->teams[i].robotCount;
        for (int j = 0; j < robotCount; ++j) {
            time_t seconds;
            time(&seconds);
            std::srand((unsigned int) seconds);
            std::shared_ptr<Rule::RobotCommand> robotCommand = std::make_shared<Rule::RobotCommand>();
            robotCommand->isTeamYellow = (i == 1);
            robotCommand->dribble = true;
            robotCommand->dribbleSpeed = 1;
            robotCommand->kick = true;
            robotCommand->kickSpeed = 2;
            robotCommand->robotId = j;
            robotCommand->stop = false;
            robotCommand->pose.coord.x = rand() % 2;
            robotCommand->pose.coord.y = rand() % 2;
            robotCommand->pose.orientation = 5;

            Rule::GameRoot::getSingleton().addRobotCommand(robotCommand);
        }
    }
}
