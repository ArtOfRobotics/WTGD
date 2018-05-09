#ifndef _GENERAL_CONTROLLER_H_
#define _GENERAL_CONTROLLER_H_

class GeneralController
{
public:
  GeneralController(ros::NodeHandle *nh, LightController *lightController, LedController *LedController);
  LightController *GetLightController();
  static ros::Publisher GetSirenPublisher();
  LedController *GetLedController();
  static ros::Publisher GetLedPublisher();


private:
};

#endif