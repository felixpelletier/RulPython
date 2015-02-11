import rule_python as rule
import math


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
                rc = rule.RobotCommand()
                rc.isTeamYellow = team.teamId == 1
                rc.dribble = True
                rc.dribbleSpeed = 1
                rc.kick = True
                rc.kickSpeed = 2
                rc.robotId = robot.robotId
                rc.stop = False
                x = 1000 - robot.pose.coord.x
                y = 1000 - robot.pose.coord.y
                magnitude = math.sqrt(x*x + y*y)
                rc.pose.coord.x = x / magnitude
                rc.pose.coord.y = y / magnitude
                rc.pose.orientation = 0 - robot.pose.orientation
                rule.sendCommand(rc)
