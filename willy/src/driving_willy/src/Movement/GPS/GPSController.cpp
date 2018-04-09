#include "../../include.h"

GPSController::GPSController()
{
    //placeholder gps values.
    GPSLatA = 52.512323;
    GPSLongA = 6.092517;
    //printf("%f\n",GPSLatA );
    GPSLatB = 52.512165;
    GPSLongB = 6.092933;

    GPSLatC = 52.512001;
    GPSLongC = 6.092820;

    GPSLatD = 52.512113;
    GPSLongD = 6.092353;
}

void GPSController::GpsCallback(const std_msgs::String::ConstPtr &msg)
{
    //printf("gps msg = %s\n", msg->data.c_str());
    std::string input = msg->data.c_str();
    std::istringstream ss(input);
    std::string token;
    int counter = 0;
    while (std::getline(ss, token, ','))
    {
        //printf("%s\n", (char *)token.c_str());
        ++counter;
    }
    // msg->data.c_str().substr (0,5);
}

//This function calculates the distance between two GPS coords in meters.
double GPSController::distanceBetweenGPS(double lat1d, double lon1d, double lat2d, double lon2d)
{
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r) / 2);
    v = sin((lon2r - lon1r) / 2);
    return 2.0 * earthRadiusMeters * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double GPSController::bearingBetweenGPS(double lat1d, double lon1d, double lat2d, double lon2d)
{
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = cos(lat1r) * sin(lat2r) - sin(lat1r) * cos(lat2r) * cos(lon2r - lon1r);
    v = sin(lon2r - lon1r) * cos(lat2r);
    return rad2deg(atan2(v, u));
}

//this function gets the gps route data stored on the ros parameter server.
void GPSController::getRouteFromParam()
{
    if (!nh->getParam("gpsLat", routeLat))
    {
        ROS_INFO("Getting gpsLat from parameter server failed!");
    }
    if (!nh->getParam("gpsLong", routeLong))
    {
        ROS_INFO("Getting gpsLong from parameter server failed");
    }
}

//This function converts decimal degrees to radians
double GPSController::deg2rad(double deg)
{
    return (deg * M_PI / 180);
}

//This function converts radians to decimal degrees
double GPSController::rad2deg(double rad)
{
    return (rad * 180 / M_PI);
}