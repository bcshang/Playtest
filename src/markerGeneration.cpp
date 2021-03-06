#include <iostream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <interactive_markers/interactive_marker_server.h>
#include <interactive_markers/menu_handler.h>


#include <Utils/wrap_eigen.hpp>
#include <Utils/utilities.hpp>

#include "helpfulMath.hpp"

int markernum = 0;


/**
 * Creates a ROS visualization marker
 * @param x coordinate of marker
 * @param y coordinate of marker
 * @param z coordinate of marker
 */
visualization_msgs::Marker createMarker(double x_pos, double y_pos, double z_pos) {
  visualization_msgs::Marker marker;

  int shape = visualization_msgs::Marker::CUBE;


  marker.header.frame_id = "/val_robot/pelvis";
  marker.header.stamp = ros::Time::now();

  marker.ns = "basic_shapes";
  marker.id = markernum;
  markernum++;

  // Set the marker shape
  marker.type = shape;

  // Set the marker action
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker
  marker.pose.position.x = x_pos;
  marker.pose.position.y = y_pos;
  marker.pose.position.z = z_pos;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  double markerSize = .08;
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = markerSize;
  marker.scale.y = markerSize;
  marker.scale.z = markerSize;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();


  return marker;
}



/**
 * Convenience wrapper for markers
 * @param  pos position of the marker
 * @return     ROS Marker message
 */
visualization_msgs::Marker createMarker(sejong::Vect3 pos) {
  return createMarker(pos[0], pos[1], pos[2]);
}

/**
 * Create a marker cylinder for visualization purposes
 * @param  radius radius
 * @param  height height
 * @return      ROS Marker message
 */
visualization_msgs::Marker createCylinder(double radius, double height, int markerID) {
  visualization_msgs::Marker marker;

  int shape = visualization_msgs::Marker::CYLINDER;
  // std::cout << "Create called with marker ID: " << markerID << std::endl;

  marker.header.frame_id = "/val_robot/pelvis";
  marker.header.stamp = ros::Time::now();

  marker.ns = "val_shapes";
  marker.id = markerID;
  markernum++;

  // Set the marker shape
  marker.type = shape;

  // Set the marker action
  marker.action = visualization_msgs::Marker::ADD;

  // Set the position of the marker
  marker.pose.position.x = 0;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;

  // set up a quaternion if we want to
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = radius*2;
  marker.scale.y = radius*2;
  marker.scale.z = height;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  return marker;
}


visualization_msgs::Marker createBox(double x_size, double y_size, double z_size, int markerID){
  visualization_msgs::Marker marker;

  int shape = visualization_msgs::Marker::CUBE;


  marker.header.frame_id = "/val_robot/pelvis";
  marker.header.stamp = ros::Time::now();

  marker.ns = "val_shapes";
  marker.id = markerID;
  markernum++;

  // Set the marker shape
  marker.type = shape;

  // Set the marker action
  marker.action = visualization_msgs::Marker::ADD;

  // Set the position of the marker
  marker.pose.position.x = 0;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;

  // set up a quaternion if we want to
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = x_size;
  marker.scale.y = y_size;
  marker.scale.z = z_size;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  return marker;

}

