## About

Example for using UTM-30LX with navigation2d of ROS node

http://daikimaekawa.github.io/ros/2014/04/20/Navigation2d/

## Install the dependency packages

```sh
$ sudo aptitude install ros-kinetic-move-base
$ sudo apt-get install ros-kinetic-hector-mapping
$ sudo apt-get install ros-kinetic-sick-tim
$ sudo apt-get install ros-kinetic-hector-trajectory-server
$ sudo apt-get install ros-kinetic-hector-geotiff
```

## Usage

```sh
$ roslaunch willy_navigation move_base.launch
```    
    
[![rviz](http://img.youtube.com/vi/c68E9-21fkw/0.jpg)](https://www.youtube.com/watch?v=c68E9-21fkw)    
    
## License

Copyright (c) 2018-2019, [Martijn van Olst](https://github.com/ArtOfRobotics/WTGD/tree/test/willy/src/willy_navigation). (MIT License)

See LICENSE for more info.
