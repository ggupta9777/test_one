#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"

double time_start = 0;
double time_prev = 0;
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void listenerCallback (const performance_tests::SuperAwesome::ConstPtr& msg)
{
  std::string recv_data = msg->data;
  double time_now = ros::Time::now().toSec ();
  // randomly sample a rate every 2 seconds
  if (time_now - time_start >= 2.0)
  {
    time_start = time_now;
    double sub_rate = 1/(time_now - time_prev);
    std::cout << "sub rate cpp: " << sub_rate << std::endl;
  }
  time_prev = time_now;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_sub_node");

  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("super_awesome_topic", 1000, listenerCallback);
  time_start = ros::Time::now ().toSec ();
  time_prev = ros::Time::now().toSec ();
  ros::spin();

  return 0;
}