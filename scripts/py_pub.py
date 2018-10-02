#!/usr/bin/env python

import rospy
import time
from performance_tests.msg import SuperAwesome
from dynamic_reconfigure.server import Server
from performance_tests.cfg import DynRateConfig

def dyn_callback (config, level):
  global rate
  pub_rate = config.rate_param
  rate = rospy.Rate (pub_rate)
  print "Py pub rate requested", pub_rate
  return config

def talker ():
  srv = Server(DynRateConfig, dyn_callback)
  string_msg = SuperAwesome ()
  string_msg.data = "another string in world"
  while not rospy.is_shutdown ():

    pub.publish (string_msg)
    rate.sleep ()

if __name__ == "__main__":

  pub = rospy.Publisher ('super_awesome_topic', SuperAwesome, queue_size=1)
  rospy.init_node ('py_pub_node')
  rate = rospy.Rate (100)
  
  try:
    talker()
  except rospy.ROSInterruptException:
    pass
