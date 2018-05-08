#ifndef _GENERAL_CONTROLLER_H_
#define _GENERAL_CONTROLLER_H_

class GeneralController
{
public:
  GeneralController(ros::NodeHandle *nh, LightController *lightController);
  LightController *GetLightController();
  static ros::Publisher GetSirenPublisher();

private:

};

#endif