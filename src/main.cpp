#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "house_action_performer/AreaName.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
MoveBaseClient* mvClient_;

bool getAreaPose(std::string area, geometry_msgs::Pose& pose) {
    if (area == "livingroom_coffeetable") {

        printf("Request to put robot at livingroom_coffeetable.\n");
        pose.position.x = 4.5;
        pose.position.y = 7.3;
        pose.position.z = 0;
        pose.orientation.z = -1.0; //tf::createQuaternionMsgFromYaw(3.141596);
        return true;

    } else if (area == "livingroom_table") {
        printf("Request to put robot at livingroom_table.\n");

        pose.position.x = 6.8;
        pose.position.y = 7.3;
        pose.position.z = 0;
        pose.orientation.w = 0.7;
        pose.orientation.z = -0.7; //tf::createQuaternionMsgFromYaw(3.141596 / 2);
        return true;
    } else if (area == "kitchen_table") {
        printf("Request to put robot at test.\n");

        pose.position.x = 7.4;
        pose.position.y = 8.3;
        pose.position.z = 0;
        pose.orientation.w = 0.7;
        pose.orientation.z = -0.7; //tf::createQuaternionMsgFromYaw(3.141596 / 2);
        return true;

    } else {
        printf("Unknown furniture: %s", area.c_str());
        return false;
    }

    /* robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "bedroom_chest":
     print("Request to put robot at bedroom_chest.")
     x_y_z_yaw_pitch_roll = {"x": 5, "y": 11.3, "z": 0, "yaw": 0.0, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "bedroom_console":
     print("Request to put robot at bedroom_console.")
     x_y_z_yaw_pitch_roll = {"x": 4.2, "y": 12.2, "z": 0, "yaw": math.pi/2, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "bedroom_bedsidetable":
     print("Request to put robot at bedroom_bedsidetable.")
     x_y_z_yaw_pitch_roll = {"x": 3.1, "y": 12.1, "z": 0, "yaw": math.pi, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "bedroom_shelf":
     print("Request to put robot at bedroom_shelf.")
     x_y_z_yaw_pitch_roll = {"x": 2.4, "y": 9.8, "z": 0, "yaw": 3*math.pi/2, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "kitchen_cupboard":
     print("Request to put robot at kitchen_cupboard.")
     x_y_z_yaw_pitch_roll = {"x": 6.7, "y": 10.6, "z": 0, "yaw": math.pi, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "kitchen_table":
     print("Request to put robot at kitchen_table")
     x_y_z_yaw_pitch_roll = {"x": 7.8, "y": 10.2, "z": 0, "yaw": math.pi/8, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   elif furniture_name == "livingroom_table":
     print("Request to put robot at livingroom_table")
     x_y_z_yaw_pitch_roll = {"x": 7.4, "y": 7.6, "z": 0, "yaw": 3*math.pi/2, "pitch": 0, "roll": 0}
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
   else:
     print("Unknown furniture: " + furniture_name)
     */
}
//////////////////////////
//Services

bool goTo(house_action_performer::AreaName::Request &req,
        house_action_performer::AreaName::Response & res) {

    move_base_msgs::MoveBaseGoal goal;

    if (getAreaPose(req.area, goal.target_pose.pose)) {

        //we'll send a goal to the robot to move 1 meter forward
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        ROS_INFO("Sending goal");
        mvClient_->sendGoal(goal);
        mvClient_->waitForResult();

        if (mvClient_->getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Hooray, the base moved to %s", req.area.c_str());
            res.answer = true;
        } else {
            ROS_INFO("The base failed to move to %s for some reason", req.area.c_str());
            res.answer = false;
        }
        return true;
    } else {
        res.answer = false;
        return false;
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "house_action_performer");

    ros::NodeHandle node;
    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);
    mvClient_ = &ac;

    //wait for the action server to come up
    while (!mvClient_->waitForServer(ros::Duration(5.0))) {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    //Services
    ros::ServiceServer serviceGoTo = node.advertiseService("house_action_performer/go_to", goTo);
    ROS_INFO("[Request] Ready to go!");

    //ros::ServiceServer serviceExplore = node.advertiseService("house_action_performer/explore", explore);
    //ROS_INFO("[Request] Ready to explore!");


    // Set this in a ros service?
    ros::Rate loop_rate(30);

    while (node.ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
