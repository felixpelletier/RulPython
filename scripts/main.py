import rule_python as rule


def update():

<<<<<<< HEAD
    print("First")
    frame = rule.getFrame();
    print("Second")
    print(frame.cameraId)

=======
>>>>>>> 7747d47795ef3dc4b2d6ddcde5590deea5daa236
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
