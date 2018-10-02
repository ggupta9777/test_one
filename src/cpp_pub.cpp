#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include <dynamic_reconfigure/server.h>
#include <performance_tests/DynRateConfig.h>

int loop_rate = 100;
ros::Rate * rate;
double time_start = 0;

void callback (performance_tests::DynRateConfig &config, uint32_t level)
{
  loop_rate = config.rate_param;
  rate = new ros::Rate (loop_rate);
  std::cout << "pub rate requested: " << loop_rate << std::endl;
}

int main(int argc, char **argv)
{
  ros::init (argc, argv, "cpp_pub_node");
  ros::NodeHandle nh;
  rate = new ros::Rate (10);
  time_start = ros::Time::now().toSec();
  dynamic_reconfigure::Server<performance_tests::DynRateConfig> server;
  dynamic_reconfigure::Server<performance_tests::DynRateConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);
  ros::Publisher pub = nh.advertise <performance_tests::SuperAwesome> ("super_awesome_topic", 10);
  performance_tests::SuperAwesome string_msg;
  string_msg.data = "another string in the world";
  double time_prev  = ros::Time::now().toSec();
  while (ros::ok ())
  {
    double time_now = ros::Time::now().toSec();
    // log the data every 2 seconds
    if (time_now - time_start >= 2)
    {
      double pub_rate = 1/(time_now - time_prev);
      time_start = time_now;
      std::cout << "rate: " << pub_rate << std::endl;
    }
    time_prev = time_now;
    pub.publish (string_msg);
    ros::spinOnce ();
    
    rate -> sleep ();
  }
  delete rate;
  return 0;
}