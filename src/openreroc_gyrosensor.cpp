#include "ros/ros.h"
#include "gyro_sensor.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct GyroSensor_Data
{
	int gx;
	int gy;
	int gz;
} gyrosensor_data;

int main(int argc, char **argv)
{
  int fd_32;
  int rc;
  
  int gyro_x;
  int gyro_y;
  int gyro_z;

  fd_32 = open("/dev/xillybus_read_32", O_RDONLY);

  ros::init(argc, argv, "openreroc_gyrosensor");
  ros::NodeHandle n;
  ros::Publisher pub_openreroc_gyrosensor = n.advertise<openreroc_gyrosensor::gyro_sensor>("gyro_sensor_value", 1000);
  // ros::Rate loop_rate(1);

  openreroc_gyrosensor::gyro_sensor msg;
  
  gyrosensor_data cur;

  while (ros::ok())
  {
    rc = read(fd_32, &gyro_x, sizeof(gyro_x));
    rc = read(fd_32, &gyro_y, sizeof(gyro_y));
    rc = read(fd_32, &gyro_z, sizeof(gyro_z));

    if(cur.gx != gyro_x && cur.gy != gyro_y && cur.gz != gyro_z){
      msg.gx = gyro_x;
      msg.gy = gyro_y;
      msg.gz = gyro_z;

      printf("x:%d\n",msg.gx);
      printf("y:%d\n",msg.gy);
      printf("z:%d\n",msg.gz);

      pub_openreroc_gyrosensor.publish(msg);
    }

    cur.gx = gyro_x;
    cur.gy = gyro_y;
    cur.gz = gyro_z;

    ros::spinOnce();
    // loop_rate.sleep();
  }

  close(fd_32);
  return 0;
}