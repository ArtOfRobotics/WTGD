#ifndef _VISION_CONTROLLER_H_
#define _VISION_CONTROLLER_H_

class VisionController
{
public:
  VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController);
  KinectController *GetKinectController();
  LidarController *GetLidarController();
  SonarController *GetSonarController();

private:
  double min_y_;   /**< The minimum y position of the points in the box. */
  double max_y_;   /**< The maximum y position of the points in the box. */
  double min_x_;   /**< The minimum x position of the points in the box. */
  double max_x_;   /**< The maximum x position of the points in the box. */
  double max_z_;   /**< The maximum z position of the points in the box. */
  double goal_z_;  /**< The distance away from the robot to hold the centroid */
  double z_scale_; /**< The scaling factor for translational robot speed */
  double x_scale_; /**< The scaling factor for rotational robot speed */
  bool enabled_;   /**< Enable/disable following; just prevents motor commands */
};

#endif