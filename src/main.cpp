#include <ros/ros.h>

#include "openprs/opaque-pub.h"
#include "openprs/mp-pub.h"

#include "house_action_performer/Name.h"
#include "house_action_performer/Empty.h"
#include "house_action_performer/Place.h"
#include "house_action_performer/Handover.h"
#include "house_action_performer/Goal.h"
#include "house_action_performer/DialInput.h"


int mpSocket_ = -1;
std::string oprsDest_ = "OPRS_SUP";

/*bool getAreaPose(std::string area, geometry_msgs::Pose& pose) {
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
        printf("Request to put robot at kitchen_table.\n");

        pose.position.x = 7.7;
        pose.position.y = 9.8;
        pose.position.z = 0;
        pose.orientation.w = 1.0;
        pose.orientation.z = 0.0; //tf::createQuaternionMsgFromYaw(3.141596 / 2);
        return true;

    } else {
        printf("Unknown furniture: %s", area.c_str());
        return false;
    }

     // This is just to get the furniture position (from some python code)
     robot_teleport.publish(x_y_z_yaw_pitch_roll)
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
     
}*/
//////////////////////////
//Services

/*bool goTo(house_action_performer::Name::Request &req,
        house_action_performer::Name::Response & res) {

    move_base_msgs::MoveBaseGoal goal;

    if (getAreaPose(req.name, goal.target_pose.pose)) {

        //we'll send a goal to the robot to move 1 meter forward
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        ROS_INFO("Sending goal");
        mvClient_->sendGoal(goal);
        mvClient_->waitForResult();

        if (mvClient_->getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Hooray, the base moved to %s", req.name.c_str());
            res.answer = true;
        } else {
            ROS_INFO("The base failed to move to %s for some reason", req.name.c_str());
            res.answer = false;
        }
        return true;
    } else {
        res.answer = false;
        return false;
    }
}
*/

bool dialIn(house_action_performer::DialInput::Request &req,
        house_action_performer::DialInput::Response & res) {

     ROS_INFO("received dialogue input: %s the %s named %s which has type %s and is on the %s in the %s to the %s in the %s", req.actionType.c_str(), req.objectType.c_str(), req.objectTitle.c_str(), req.objectCategory.c_str(), req.furnitureSubject.c_str(), req.roomSubject.c_str(), req.furnitureTarget.c_str(), req.roomTarget.c_str());

    //send a message to oprs
    /*std::string strmessage = "(RequestManager.request (. .) house_action_performer)";
    char returnMessage[100];
    strcpy(returnMessage, strmessage.c_str());
    send_message_string(returnMessage, oprsDest_.c_str());


    //read the openprs message
    int length;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);

*/
    return true;
}



bool explore(house_action_performer::Empty::Request &req,
        house_action_performer::Empty::Response & res) {


    
    //send a message to oprs
    std::string strmessage = "(RequestManager.request explore (. .) house_action_performer)";
    char returnMessage[100];
    strcpy(returnMessage, strmessage.c_str());
    send_message_string(returnMessage, oprsDest_.c_str());



    //read the openprs message
    int length;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);


    return true;
}

bool pick(house_action_performer::Name::Request &req,
        house_action_performer::Name::Response & res) {

    //send a message to oprs
    std::stringstream ss;
    ss << "(requestManager.request pick (. " << req.name << " .) house_action_performer)";

    char returnMessage[100];
    strcpy(returnMessage, ss.str().c_str());
    send_message_string(returnMessage, oprsDest_.c_str());


    //read the openprs message
    int length;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);

    res.answer = true;

    return true;
}

bool place(house_action_performer::Place::Request &req,
        house_action_performer::Place::Response & res) {

    //send a message to oprs
    std::stringstream ss;
    ss << "(RequestManager.request pick (. " << req.furnitureName << " " << req.objectName << " .) house_action_performer)";
    char returnMessage[50];
    strcpy(returnMessage, ss.str().c_str());
    send_message_string(returnMessage, oprsDest_.c_str());


    //read the openprs message
    int length;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);


    return true;
}

bool handover(house_action_performer::Handover::Request &req,
        house_action_performer::Handover::Response & res) {

    //send a message to oprs
    std::stringstream ss;
    ss << "(RequestManager.request pick (. " << req.agentName << " " << req.objectName << " .) house_action_performer)";
    char returnMessage[100];
    strcpy(returnMessage, ss.str().c_str());
    send_message_string(returnMessage, oprsDest_.c_str());


    //read the openprs message
    int length;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);


    return true;
}

bool sendGoal(house_action_performer::Goal::Request &req,
        house_action_performer::Goal::Response & res) {

    //send a message to oprs
    printf("received request to send goal\n");
    std::stringstream ss;
    ss << "(RequestManager.request " << req.goal <<  " (. " << req.areaName << " " << req.objectName << " " << req.locationName << " " << req.agentName << " .) house_action_performer)";
    char returnMessage[100];
    strcpy(returnMessage, ss.str().c_str());
    send_message_string(returnMessage, oprsDest_.c_str());


    //read the openprs message
    int length = 0;
    char *sender = read_string_from_socket(mpSocket_, &length);
    char *message = read_string_from_socket(mpSocket_, &length);

    res.answer = true;
    printf("request send to oprs\n");
    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "house_action_performer");

    ros::NodeHandle node;
    //tell the action client that we want to spin a thread by default
    //MoveBaseClient ac("move_base", true);
    //mvClient_ = &ac;

    //wait for the action server to come up
//    while (!mvClient_->waitForServer(ros::Duration(5.0))) {
  //      ROS_INFO("Waiting for the move_base action server to come up");
   // }

    //Services
  //  ros::ServiceServer serviceGoTo = node.advertiseService("house_action_performer/go_to", goTo);
  //  ROS_INFO("[Request] Ready to go!");

    ros::ServiceServer serviceDialIn = node.advertiseService("house_action_performer/dialogue", dialIn);
    ROS_INFO("[Request] Ready to get dialogue input!");

    ros::ServiceServer serviceExplore = node.advertiseService("house_action_performer/explore", explore);
    ROS_INFO("[Request] Ready to explore!");

    ros::ServiceServer servicePick = node.advertiseService("house_action_performer/pick", pick);
    ROS_INFO("[Request] Ready to pick!");

    ros::ServiceServer servicePlace = node.advertiseService("house_action_performer/place", place);
    ROS_INFO("[Request] Ready to place!");

    ros::ServiceServer serviceHandover = node.advertiseService("house_action_performer/give", handover);
    ROS_INFO("[Request] Ready to give!");

    ros::ServiceServer servicesendGoal = node.advertiseService("house_action_performer/send_goal", sendGoal);
    ROS_INFO("[Request] Ready to send_goal!");
    
    //ros::ServiceServer serviceExplore = node.advertiseService("house_action_performer/explore", explore);
    //ROS_INFO("[Request] Ready to explore!");


    while (mpSocket_ == -1) {
        mpSocket_ = external_register_to_the_mp_prot("house_action_performer", 3300, STRINGS_PT);
        printf("Waiting For oprs ...");
    }

    printf("Successfully connected to oprs :)");

    // Set this in a ros service?
    ros::Rate loop_rate(30);

    while (node.ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
