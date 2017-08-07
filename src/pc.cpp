#include "ros/ros.h"
#include "arduino_pc/Arduino.h"
#include "arduino_pc/PC.h"
#include "navigation/Navigation.h"
#include "std_msgs/String.h"

// Subscribers
ros::Subscriber navigation_sub;
ros::Subscriber arm_state_sub;

// Publisher
ros::Publisher pc_pub;

//Publisher msgs
arduino_pc::PC pc_msg;

void arm_state_callback(const std_msgs::String arm_state_msg) {
	if(arm_state_msg.data.compare("in_progress")==0)
		pc_msg.relay_state=true;
	else if(arm_state_msg.data.compare("pickup_done")==0)
		pc_msg.relay_state=false;
	else
		pc_msg.relay_state=false;
}

void navigation_callback(const navigation::Navigation navigation_msg) {
	pc_msg.l_motor_val = navigation_msg.l_motor_val;
	pc_msg.r_motor_val = navigation_msg.r_motor_val;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "pc");

	ros::NodeHandle n;

	navigation_sub = n.subscribe("navigation", 1000, navigation_callback);
	arm_state_sub = n.subscribe("arm_state", 1000, arm_state_callback);

	pc_pub = n.advertise<arduino_pc::PC>("pc", 1000);

	ros::Rate loop_rate(10);

	while(ros::ok()) {

	    pc_pub.publish(pc_msg);

	    ros::spinOnce();
	    loop_rate.sleep();
	}
}
