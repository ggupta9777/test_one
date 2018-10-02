#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"

// number of callbacks between any two seconds
double counts = 0;

/**
 * @brief callback for the custom message
 * @details reads the message, updates the count
 * 
 * @param msg [description]
 */
void listenerCallback (const performance_tests::SuperAwesome::ConstPtr& msg)
{
  std::string recv_data = msg->data;
  counts = counts + 1; 
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_sub_node");

  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("super_awesome_topic", 1, listenerCallback);
  double time_start = ros::Time::now ().toSec ();
  double time_now = ros::Time::now().toSec ();
  while (ros::ok ())
  {
    time_now = ros::Time::now().toSec();
    if (time_now - time_start >= 2.0)
    { 
      double average_rate = counts/(time_now - time_start);
      ROS_INFO ("CPP: average sub rate for past 2 seconds: %f", average_rate);
      time_start = time_now;
      counts = 0;
    }
    ros::spinOnce();
  }
  return 0;
}