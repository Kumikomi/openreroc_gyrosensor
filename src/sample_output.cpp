#include "ros/ros.h"
#include "gyro_sensor.h"
#include <stdio.h>

void chatterCallback(const openreroc_gyrosensor::gyro_sensor msg)
{
    printf("x:%f\n",msg.real_gx);
    printf("y:%f\n",msg.real_gy);
    printf("z:%f\n",msg.real_gz);
}

int main(int argc, char  **argv)
{
	ros::init(argc, argv, "sample_output");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("gyro_sensor_value", 1000, chatterCallback);
	ros::spin();
  	return 0;
}
