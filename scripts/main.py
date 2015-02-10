import rule_python as rule


def update(vision_frames):

    print("into Python")
    print("vision_frames size: " + str(len(vision_frames)))
    if vision_frames:
        team = vision_frames[0].teams[0]
        robot = team.robots[0]
        coords = robot.pose.coord
        print("vision_frames[0].teams[0].robots[0].pose.coord.x: "
              + str(coords.x))
    #print("First")
    #frame = rule.getFrame();
    #print("Second")
    #print(frame.cameraId)

    for i in range(2):
        for j in range(5):
            rc = rule.RobotCommand()
            rc.isTeamYellow = i == 1
            rc.dribble = True
            rc.dribbleSpeed = 1
            rc.kick = True
            rc.kickSpeed = 2
            rc.robotId = j
            rc.stop = False
            rc.pose.coord.x = 1
            rc.pose.coord.y = 2
            rc.pose.orientation = 5
            rule.sendCommand(rc)
