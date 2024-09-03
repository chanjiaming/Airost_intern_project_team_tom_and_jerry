#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Pose, PoseStamped, Point, Quaternion
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import actionlib

def send_waypoints(client, waypoints):
    for i, waypoint in enumerate(waypoints):
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()

        goal.target_pose.pose = waypoint

        rospy.loginfo(f"Sending waypoint {i+1}")
        client.send_goal(goal)
        client.wait_for_result(rospy.Duration.from_sec(40.0))  # Wait for a max of 10 seconds
        rospy.loginfo(f"Waypoint {i+1} reached or timeout reached")

if __name__ == '__main__':
    rospy.init_node('navigation_with_waypoints')

    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    client.wait_for_server()

    # Define multiple waypoints
    waypoints = [
        Pose(position=Point(2.46, 2.36, 0.00101), orientation=Quaternion(0.0, 0.0, 0.0, 1.0)),
        Pose(position=Point(1.31, 3.55, 0.0031), orientation=Quaternion(0.0, 0.0, 0.707, 0.707)),
        #Pose(position=Point(2.3, 1.5, 0.00244), orientation=Quaternion(0.0, 0.0, 0.0, 1.0)),
        ]

    # Send the waypoints to the robot
    send_waypoints(client, waypoints)

    rospy.loginfo("All waypoints processed")
