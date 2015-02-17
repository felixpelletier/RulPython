import rule_python as rule


def update(vision_frames, referee_commands):

    print("into Python")
    print("vision_frames size: " + str(len(vision_frames)))
    if vision_frames:
        team = vision_frames[0].teams[0]
        robot = team.robots[0]
        coords = robot.pose.coord
        print("vision_frames[0].teams[0].robots[0].pose.coord.x: "
              + str(coords.x))

    print("referee_commands size: " + str(len(referee_commands)))
    if referee_commands:
        command = referee_commands[0].command
        print("referee_commands[0].command.name: "
              + str(command.name))

    if vision_frames:
        for team in vision_frames[-1].teams:
            for robot in team.robots:
                rc = rule.RobotCommand(robot)
                rc.isTeamYellow = team.teamId
                rc.dribble = True
                rc.dribbleSpeed = 1
                rc.kick = True
                rc.kickSpeed = 2
                rc.stop = False
                rc.pose.coord.x = 1
                rc.pose.coord.y = 2
                rc.pose.orientation = 5
                rule.sendCommand(rc)
