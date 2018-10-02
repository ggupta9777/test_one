#!/usr/bin/env python

import rospy
import time
from performance_tests.msg import SuperAwesome
from dynamic_reconfigure.server import Server
from performance_tests.cfg import DynRateConfig

counts = 0

def listenerCallback (msg):
  global counts
  data = msg.data
  counts = counts + 1

def init ():
  global time_start, counts
  rospy.Subscriber("super_awesome_topic", SuperAwesome, listenerCallback)
  while not rospy.is_shutdown ():
    time_now = time.time ()
    if (time_now - time_start) > 2.0:
      avg_rate = counts/(time_now - time_start)
      print ("Py: average sub rate for past 2 seconds: %f", avg_rate)
      time_start = time_now;
      counts = 0

if __name__ == "__main__":

  rospy.init_node ('py_sub_node')
  time_now = time.time ()
  time_start = time_now

  try:
    init ()
  except rospy.ROSInterruptException:
    pass

  time_now = time.time ()
