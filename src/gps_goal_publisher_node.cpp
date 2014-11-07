#include <ros/ros.h>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Bool.h>
// ifstream constructor.
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
using namespace std;

ros::Publisher goal_publisher;
bool next = true;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "gps_goal_publisher");
	ros::NodeHandle n;
	goal_publisher = n.advertise<sensor_msgs::NavSatFix>("gps_goal", 10);
	sensor_msgs::NavSatFix msg;
	msg.header.stamp = ros::Time::now();
	double gpsPoint[2];
	ifstream inputFile("/home/irl/gps_waypoints.txt");
	ros::Rate loop_rate(4);

	while(ros::ok())
	{
		if(next==true)
		{
			//ROS_INFO("here");
			next = false;
			if (inputFile) 
			{        
			    float value1,value2;
			    inputFile >> value1;
			    gpsPoint[0]=(value1);
			    inputFile >> value2;
			    gpsPoint[1]=(value2);
			    ROS_INFO("setting new goal to %f %f",value1,value2);
			}

		}
		msg.latitude = gpsPoint[0];
		msg.longitude =  gpsPoint[1];
		goal_publisher.publish(msg);
		ros::spinOnce();
	    loop_rate.sleep();
	}
	return 0;
}