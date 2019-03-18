#ifndef LOCAL_PLANNER_VISUALIZATION_H
#define LOCAL_PLANNER_VISUALIZATION_H

#include "local_planner/local_planner.h"

#include <pcl/point_cloud.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <Eigen/Dense>
#include <vector>

namespace avoidance {

class LocalPlannerVisualization {
 public:
  /**
  * @brief      initializes all subscribers used for local planner visualization
  **/
  void initializeSubscribers(ros::NodeHandle& nh);

  /**
  * @brief       Main function which calls functions to visualize all planner
  *output ready at the end of one planner iteration
  * @params[in] planner, reference to the planner
  **/
  void visualizePlannerData(LocalPlanner& planner);

  /**
  * @brief       Visualization of the calculated search tree and the best path
  *chosen
  * @params[in]  tree, the complete calculated search tree
  * @params[in]  closed_set, the closed set (all expanded nodes)
  * @params[in]  path_node_positions, the positions of all nodes belonging to
  *the chosen best path
  **/
  void publishTree(std::vector<TreeNode>& tree,
                   const std::vector<int> closed_set,
                   const std::vector<Eigen::Vector3f> path_node_positions);

  /**
  * @brief       Visualization of the goal position
  * @params[in]  goal, the loaction of the goal used in the planner calculations
  **/
  void publishGoal(const geometry_msgs::Point goal);

  /**
  * @brief       Visualization of the bounding box used to crop the pointcloud
  * @params[in]  drone_pos, current position of the drone
  * @params[in]  box_radius, the radius of the bounding box
  * @params[in]  plane_height, the height above ground at which the pointcloud
  *is additionally cropped
  **/
  void publishBox(const Eigen::Vector3f drone_pos, const float box_radius,
                  const float plane_height);

  /**
  * @brief       Visualization of the data used during takeoff
  * @params[in]  take_off_pose, pose at which the vehicle was armed
  * @params[in]  starting_height, height at which the planner starts planning
  *forward
  **/
  void publishReachHeight(const Eigen::Vector3f& take_off_pose,
                          const float starting_height);

  /**
  * @brief       Visualization of the 2D compression of the local pointcloud
  * @params[in]  histogram_image, data for visualization
  * @params[in]  cost_image, data for visualization
  **/
  void publishDataImages(const std::vector<uint8_t>& histogram_image_data, const std::vector<uint8_t>& cost_image_data);

  /**
  * @brief       Visualization of the waypoint calculation
  * @params[in]  goto_position, original calulated desired direction
  * @params[in]  adapted_goto_position, desired direction adapted to the desired
  *speed
  * @params[in]  smoothed_goto_position, smoothed waypoint which is given to the
  *controller
  **/
  void visualizeWaypoints(const Eigen::Vector3f& goto_position,
                          const Eigen::Vector3f& adapted_goto_position,
                          const Eigen::Vector3f& smoothed_goto_position);

  /**
  * @brief       Visualization of the actual path of the drone and the path of
  *the waypoint
  * @params[in]  last_pos, location of the drone at the last timestep
  * @params[in]  newest_pos, location of the drone at the current timestep
  * @params[in]  last_wp, location of the smoothed waypoint at the last timestep
  * @params[in]  newest_wp, location of the smoothed waypoint at the current
  *timestep
  * @params[in]  last_adapted_wp, location of the adapted waypoint at the last
  *timestep
  * @params[in]  newest_adapted_wp, location of the adapted waypoint at the
  *current timestep
  **/
  void publishPaths(const geometry_msgs::Point last_pos,
                    const geometry_msgs::Point newest_pos,
                    const geometry_msgs::Point last_wp,
                    const geometry_msgs::Point newest_wp,
                    const geometry_msgs::Point last_adapted_wp,
                    const geometry_msgs::Point newest_adapted_wp);

  /**
  * @brief       Visualization of the sent waypoint color coded with the mode
  *the planner is in
  * @params[in]  wp, sent wayoint
  * @params[in]  waypoint_type, current planner mode to color code the
  *visualization
  * @params[in]  newest_pos, location of the drone at the current timestep
  **/
  void publishCurrentSetpoint(const geometry_msgs::Twist& wp,
                              waypoint_choice& waypoint_type,
                              const geometry_msgs::Point newest_pos);

  /**
  * @brief       Visualization of the ground
  * @params[in]  drone_pos, location of the drone at the current timestep
  * @params[in]  box_radius, the radius of the bounding box
  * @params[in]  ground_distance, measured distance to ground
  **/
  void publishGround(const Eigen::Vector3f& drone_pos, const float box_radius,
                     const float ground_distance);

 private:
  ros::Publisher local_pointcloud_pub_;
  ros::Publisher reprojected_points_pub_;
  ros::Publisher bounding_box_pub_;
  ros::Publisher ground_measurement_pub_;
  ros::Publisher original_wp_pub_;
  ros::Publisher adapted_wp_pub_;
  ros::Publisher smoothed_wp_pub_;
  ros::Publisher complete_tree_pub_;
  ros::Publisher tree_path_pub_;
  ros::Publisher marker_goal_pub_;
  ros::Publisher path_actual_pub_;
  ros::Publisher path_waypoint_pub_;
  ros::Publisher path_adapted_waypoint_pub_;
  ros::Publisher current_waypoint_pub_;
  ros::Publisher takeoff_pose_pub_;
  ros::Publisher initial_height_pub_;
  ros::Publisher histogram_image_pub_;
  ros::Publisher cost_image_pub_;

  int path_length_ = 0;
};
}
#endif  // LOCAL_PLANNER_VISUALIZATION_H
