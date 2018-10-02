#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include <dynamic_reconfigure/server.h>
#include <performance_tests/DynRateConfig.h>

int loop_rate = 100;
ros::Rate * rate;

/**
 * @brief callback for dynamic reconfig
 * @details reads the config message and writes the rate to global variable
 * 
 * @param config [description]
 * @param level [description]
 */
void callback (performance_tests::DynRateConfig &config, uint32_t level)
{
  loop_rate = config.rate_param;
  rate = new ros::Rate (loop_rate);
  ROS_WARN("CPP: pub rate requested: %d", loop_rate);
}

int main(int argc, char **argv)
{
  ros::init (argc, argv, "cpp_pub_node");
  ros::NodeHandle nh;
  rate = new ros::Rate (10);
  dynamic_reconfigure::Server<performance_tests::DynRateConfig> server;
  dynamic_reconfigure::Server<performance_tests::DynRateConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);
  ros::Publisher pub = nh.advertise <performance_tests::SuperAwesome> ("super_awesome_topic", 1);
  performance_tests::SuperAwesome string_msg;
  string_msg.data = "another string in the world";
  while (ros::ok ())
  {
    pub.publish (string_msg);
    ros::spinOnce ();
    rate -> sleep ();
  }
  delete rate;
  return 0;
}