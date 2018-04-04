#pragma once
#ifndef _KINECT_CONTROLLER_H_
#define _KINECT_CONTROLLER_H_

class KinectController
{
  public:
    //Constructor
    KinectController(WillyController *Controller, int argc, char **argv);
    void Start();

  private:
    WillyController *_controller;
    volatile bool running = true;
    void depth_cb(freenect_device *dev, void *data, uint32_t timestamp);
    void video_cb(freenect_device *dev, void *data, uint32_t timestamp);
    void signalHandler(int signal);
};

#endif