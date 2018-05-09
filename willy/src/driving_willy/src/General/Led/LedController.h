#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_

class LedController
{
  public:
    //Constructor
    LedController();
    void LedCallback(const std_msgs::Char input);

  private:
};

#endif