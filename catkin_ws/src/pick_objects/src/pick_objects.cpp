#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int16.h>

std_msgs::Int16 status;

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Publisher status_pub = n.advertise<std_msgs::Int16>("/current_status", 1000);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  status.data = 0;
  status_pub.publish(status);

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.22068214417;
  goal.target_pose.pose.position.y = 0.562308967113;
  goal.target_pose.pose.position.z = 1.0;
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.958363905623;
  goal.target_pose.pose.orientation.w = -0.285549688144;
  

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      status.data = 1;
      for (int i = 0;i <1000;i++)
      status_pub.publish(status);
      ROS_INFO("Pickup Zone Reached");
    }
  else
    ROS_INFO("Move_failed");

  ros::Duration(5).sleep();
  status.data = 2;
  status_pub.publish(status);


  goal.target_pose.pose.position.x = -1.66772055626;
  goal.target_pose.pose.position.y = -2.02861714363;
  goal.target_pose.pose.position.z = 0.0;
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.324731128264;
  goal.target_pose.pose.orientation.w = 0.945806372539;
  

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      status.data = 3;
      status_pub.publish(status);
      ROS_INFO("Dropoff Zone Reached");
    }
  else
    ROS_INFO("Move_failed");

  return 0;
}
