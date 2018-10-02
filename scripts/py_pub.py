#!/usr/bin/env python

import rospy
from performance_tests.msg import SuperAwesome
from dynamic_reconfigure.server import Server
from performance_tests.cfg import DynRateConfig

def dyn_callback (config, level):
  global rate
  pub_rate = config.rate_param
  rate = rospy.Rate (pub_rate)
  print "pub rate requested", pub_rate
  return config

def talker ():
  global time_start, time_prev
  srv = Server(DynRateConfig, dyn_callback)
  string_msg = SuperAwesome ()
  string_msg.data = "another string in world"
  while not rospy.is_shutdown ():
    time_now = rospy.get_time ()
    if ((time_now - time_start) > 2.0):
      time_start = time_now
      print time_now, time_prev
      print "pub rate py: ", 1/(time_now-time_prev)
    time_prev = time_now
    pub.publish (string_msg)
    rate.sleep ()

if __name__ == "__main__":

  pub = rospy.Publisher ('super_awesome_topic', SuperAwesome, queue_size=10)
  rospy.init_node ('py_pub_node')
  time_now = rospy.get_time()
  time_prev = time_now
  time_start = time_now

  rate = rospy.Rate (100)
  
  try:
    talker()
  except rospy.ROSInterruptException:
    pass
