#!/usr/bin/env python

# Authors: Aaron Rito, Robert Lockard
# Date: 10/16/17
# Client: ROB456 HW2
# Citaions/Help: Student Corwin Perren gave us the critical tip that the laser has 1080

import rospy
import math
import tf
from tf.transformations import euler_from_quaternion
import message_filters

# The laser scan message
from sensor_msgs.msg import LaserScan

# The odometry message
from nav_msgs.msg import Odometry

# the velocity command message
from geometry_msgs.msg import Twist

# instantiate global variables "globalOdom"
globalOdom = Odometry()

# global pi - this may come in handy
pi = math.pi


#########MODIFIED GLOBALS####################################################################
# range of scans we want to use, we want forward facing results. 
# the scanner takes 1080 scans, so:

# might hit object threshold
object_hit_threshold = 1.5

# set the laser that points forward (middle = 1080/2), this is how we tell left from right.....
front_laser = 540

# set the threshold for how far the laser scanner should spread
scan_threshold = 235

# set the low range (left)
scan_low = front_laser - scan_threshold

# set the high range (right)
scan_high = front_laser + scan_threshold

# set the threshold for turning towards target 
# the formula is "difference = currentAngle - desired_angle"
turn_threshold = 0.1

# set the distance to what is close enough to be a goal
goal_threshold = 0.1

# method to control the robot
def callback(scan,odom):
    # the odometry parameter should be global
    global globalOdom
    globalOdom = odom

    # make a new twist message
    command = Twist()
    # flags for turning when going to hit somthing
    turn_right_flag = False
    turn_left_flag = False
    # Fill in the fields.  Field values are unspecified 
    # until they are actually assigned. The Twist message 
    # holds linear and angular velocities.
    command.linear.x = 0.0
    command.linear.y = 0.0
    command.linear.z = 0.0
    command.angular.x = 0.0
    command.angular.y = 0.0
    command.angular.z = 0.0

    # get goal x and y locations from the launch file
    goalX = rospy.get_param('hw2/goalX',0.0)
    goalY = rospy.get_param('hw2/goalY',0.0)
    
    # find current (x,y) position of robot based on odometry
    currentX = globalOdom.pose.pose.position.x
    currentY = globalOdom.pose.pose.position.y

    # find current orientation of robot based on odometry (quaternion coordinates)
    xOr = globalOdom.pose.pose.orientation.x
    yOr = globalOdom.pose.pose.orientation.y
    zOr = globalOdom.pose.pose.orientation.z
    wOr = globalOdom.pose.pose.orientation.w

    # find orientation of robot (Euler coordinates)
    (roll, pitch, yaw) = euler_from_quaternion([xOr, yOr, zOr, wOr])

    # find currentAngle of robot (equivalent to yaw)
    # now that you have yaw, the robot's pose is completely defined by (currentX, currentY, currentAngle)
    currentAngle = yaw
   
    # find laser scanner properties (min scan angle, max scan angle, scan angle increment)
    maxAngle = scan.angle_max
    minAngle = scan.angle_min
    angleIncrement = scan.angle_increment

    # find current laser angle, max scan length, distance array for all scans, and number of laser scans
    currentLaserTheta = minAngle
    maxScanLength = scan.range_max 
    distanceArray = scan.ranges
    numScans = len(distanceArray)

    ##############BEGIN MODIFICATIONS#########################
    # Find the angle to the desired point, then find the difference between 
    # the bot's current trajectory and the goal angle. 
    desired_angle = math.atan2(goalY - currentY, goalX - currentX)
    difference = currentAngle - desired_angle
   
    # debugging lines
    #print 'x: {0}'.format(currentX)
    #print 'y: {0}'.format(currentY)
    #print 'bot trajectory: {0}'.format(currentAngle)
    #print 'desired angle: {0}'.format(desired_angle)
    #print 'difference: {0}'.format(difference)

    # for laser scan in forward pointing lasers
    for curScan in range(scan_low, scan_high):	
        # if any of the scans come back under the obstcale threshold,
	# set the appropriate turn flag and break out of the loop.
        # this is nice because it avoids comparing all the 1080 scans
        # and if its too close it stops comparing anymore entries.
        # it also keeps the runtime modest by avoiding embedded loops.
	if distanceArray[curScan] < object_hit_threshold:
		if curScan < front_laser:
			turn_right_flag = True
			break
		elif curScan > front_laser:
			turn_left_flag = True
			break		
	currentLaserTheta = currentLaserTheta + angleIncrement	
    
    # check to see if the robot is at (close to) the goal, leave the program if it is (Citation: Corwin Perren)
    if (abs(goalX - currentX) < goal_threshold) and (abs(goalY - currentY) < goal_threshold):
	print "The bot has reached its goal!!!!!"
	quit()

    # always go forward and straight
    command.linear.x = 0.7
    command.angular.z = 0.0

    # if the obstacle flags are raised, turn the bot and reset the flag
    if turn_right_flag:
	command.angular.z = 1.5

	turn_right_flag = False
    elif turn_left_flag:
	command.angular.z = -1.5
	turn_left_flag = False
    
    # check if the bot is headed the right direction
    # if it strays from its goal trajectory make it turn towards it.
    # if difference angle is less than the turning threshold (close to 0) 
    # then the bot is on the right path (it will never completely equal 0) 
    elif abs(difference) > turn_threshold:
	if difference > 0:	
	    command.angular.z = -0.4
	elif difference < 0:
	    command.angular.z = 0.4
    pub.publish(command)

# main function call
if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('lab2', log_level=rospy.DEBUG)

    # subscribe to laser scan message
    sub = message_filters.Subscriber('base_scan', LaserScan)

    # subscribe to odometry message    
    sub2 = message_filters.Subscriber('odom', Odometry)

    # synchronize laser scan and odometry data
    ts = message_filters.TimeSynchronizer([sub, sub2], 10)
    ts.registerCallback(callback)

    # publish twist message
    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)

    # Turn control over to ROS
    rospy.spin()

