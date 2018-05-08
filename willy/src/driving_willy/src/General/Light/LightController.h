#ifndef _LIGHT_CONTROLLER_H_
#define _LIGHT_CONTROLLER_H_

class LightController
{
  public:
    //Constructor
    LightController();
    void LightCallback(const std_msgs::Char &msg);

  private:
};

#endif