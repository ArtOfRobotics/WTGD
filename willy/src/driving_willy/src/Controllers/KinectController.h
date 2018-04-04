#ifndef _KINECT_CONTROLLER_H_
#define _KINECT_CONTROLLER_H_

#include "../Includes/OpenKinect/include/libfreenect.h"

class KinectController
{
  public:
    //Constructor
    KinectController(int argc, char **argv);
    void Start();

  private:
    volatile bool running = true;
    void depth_cb(freenect_device *dev, void *data, uint32_t timestamp);
    void video_cb(freenect_device *dev, void *data, uint32_t timestamp);
    void signalHandler(int signal);
};

#endif