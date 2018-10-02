#!/usr/bin/env python

import rospy
from performance_tests.msg import SuperAwesome

def listenerCallback (msg):
  global time_prev, time_start
  data = msg.data
  time_now = rospy.get_time ()
  if (time_now - time_start >= 2.0):
    time_start = time_now
    print "sub rate py: ", 1.0/(time_now - time_prev)
  time_prev = time_now

def init ():
  global time_start, time_prev
  rospy.Subscriber("super_awesome_topic", SuperAwesome, listenerCallback)
  rospy.spin ()
  
if __name__ == "__main__":

  rospy.init_node ('py_sub_node')
  time_now = rospy.get_time()
  time_prev = time_now
  time_start = time_now
  
  try:
    init ()
  except rospy.ROSInterruptException:
    pass
