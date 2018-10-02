#!/usr/bin/env python

import rospy
import time
from performance_tests.msg import SuperAwesome
from dynamic_reconfigure.server import Server
from performance_tests.cfg import DynRateConfig

# number of callbacks
counts = 0

"""
  callback for the string message, update the count
"""
def listener_callback (msg):
  global counts
  data = msg.data
  counts = counts + 1

"""
  sets up the subscriber and logs the rate
"""
def talker ():
  global time_start, counts
  rospy.Subscriber("super_awesome_topic", SuperAwesome, listener_callback)
  while not rospy.is_shutdown ():
    time_now = time.time ()
    # print the rate at every two seconds, reset the count
    if (time_now - time_start) > 2.0:
      avg_rate = counts/(time_now - time_start)
      rospy.loginfo ("Py: average sub rate for past 2 seconds: %f", avg_rate)
      time_start = time_now;
      counts = 0

if __name__ == "__main__":

  rospy.init_node ('py_sub_node')
  time_now = time.time ()
  time_start = time_now
  talker ()