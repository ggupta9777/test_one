#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void listenerCallback (const performance_tests::SuperAwesome::ConstPtr& msg)
{
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_sub_node");

  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("super_awesome_topic", 1000, listenerCallback);

  ros::spin();

  return 0;
}