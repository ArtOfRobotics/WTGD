#ifndef _GPS_CONTROLLER_H_
#define _GPS_CONTROLLER_H_

class GPSController
{
  public:
    //Constructor
    GPSController();
    void GpsCallback(const std_msgs::String::ConstPtr &msg);
    double GPSLatA, GPSLongA, GPSLatB, GPSLongB, GPSLatC, GPSLongC, GPSLatD, GPSLongD, GPSCurrentLat, GPSCurrentLong;
    std::vector<double> routeLat;
    std::vector<double> routeLong;
    void getRouteFromParam();

  private:
    double distanceBetweenGPS(double lat1d, double lon1d, double lat2d, double lon2d);
    double bearingBetweenGPS(double lat1d, double lon1d, double lat2d, double lon2d);
    double rad2deg(double rad);
    double deg2rad(double deg);
};

#endif