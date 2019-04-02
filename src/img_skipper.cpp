#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"

#include <sstream>

double last_time=0;
ros::Publisher img_pub;
ros::Subscriber img_sub;

void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    if(img_msg->header.stamp.toSec()-last_time<0.06)
    {
        return;
    }
    else
    {
        img_pub.publish(img_msg);
        last_time = img_msg->header.stamp.toSec();
    }
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_skipper");
    ros::NodeHandle n;

    img_pub = n.advertise<sensor_msgs::Image>("skipper/image", 2000);
    img_sub = n.subscribe("/cam0/image_raw", 1000, img_callback);

    ros::spin();
    return 0;
}