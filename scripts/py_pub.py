#!/usr/bin/env python

import rospy
from performance_tests.msg import SuperAwesome

def talker ():
  pub = rospy.Publisher ('super_awesome_topic', SuperAwesome, queue_size=10)
  rospy.init_node ('pypub_node')
  rate = rospy.Rate (10)
  while not rospy.is_shutdown ():
    string_msg = SuperAwesome ()
    string_msg.data = "another string in world"
    pub.publish (string_msg)
    rate.sleep ()

if __name__ == "__main__":
  try:
    talker()
  except rospy.ROSInterruptException:
    pass
