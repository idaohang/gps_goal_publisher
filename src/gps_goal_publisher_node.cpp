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
ros::Rate loop_rate(4);


int main(int argc, char **argv)
{
	ros::init(argc, argv, "gps_goal_publisher");
	ros::NodeHandle n;
	goal_publisher = n.advertise<sensor_msgs::NavSatFix>("gps_goal", 10);
	sensor_msgs::NavSatFix msg;
	msg.header.stamp = ros::Time::now();
	double gpsPoint[2];
	ifstream inputFile("~/gps_waypoints.txt");
	while(ros::ok())
	{
		if(next==true)
		{
			next = false;
			if (inputFile) 
			{        
			    double value;
			    inputFile >> value;
			    gpsPoint[0]=(value);
			    inputFile >> value;
			    gpsPoint[1]=(value);
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