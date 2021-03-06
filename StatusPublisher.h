#ifndef STATUSPUBLISHER_H
#define STATUSPUBLISHER_H

#include "XQ4IO.h"

//#include "ros/ros.h"
//#include <boost/thread.hpp>
//#include <boost/assign/list_of.hpp>
#include <algorithm>
//#include "geometry_msgs/Pose2D.h"
//#include "geometry_msgs/Twist.h"
//#include "geometry_msgs/Vector3.h"
//#include "nav_msgs/Odometry.h"
//#include "std_msgs/Int32.h"
//#include "std_msgs/Float64.h"
//#include "tf/transform_broadcaster.h"
//#include <sensor_msgs/point_cloud2_iterator.h>
//#include <sensor_msgs/PointField.h>
//#include <sensor_msgs/Imu.h>

//#include <cscv/macxx.h>
#include "maros.h"
//#include <rclcpp/rclcpp.hpp>
//#include <tf2_ros/transform_listener.h>


#define PI 3.14159265

namespace xqserial_server
{
//typedef struct
//{
//    int status;              //小车状态，0表示未初始化，1表示正常，-1表示error
//    float power;             //电源电压【9 13】v
//    float theta;             //方位角，【0 360）°
//    int encoder_ppr;         //车轮1转对应的编码器个数
//    int encoder_delta_r;     //右轮编码器增量， 个为单位
//    int encoder_delta_l;     //左轮编码器增量， 个为单位
//    int encoder_delta_car;   //两车轮中心位移，个为单位
//    int omga_r;              //右轮转速 个每秒
//    int omga_l;              //左轮转速 个每秒
//    float distance1;         //第一个超声模块距离值 单位cm
//    float distance2;         //第二个超声模块距离值 单位cm
//    float distance3;         //第三个超声模块距离值 单位cm
//    float distance4;         //第四个超声模块距离值 单位cm
//    float IMU[9];            //mpu9250 9轴数据
//    unsigned int time_stamp; //时间戳
//} UPLOAD_STATUS;

class StatusPublisher
{

  public:
    void StatusPublisher1();
    StatusPublisher(double separation, double radius, XQ4IO *sta_serial_, std::shared_ptr<rclcpp::Node> nodeHandler);
    void Refresh();
    void Update();
    double get_wheel_separation();
    double get_wheel_radius();
    int get_wheel_ppr();
    int get_status();
    geometry_msgs::msg::Pose2D get_CarPos2D();
    void get_wheel_speed(double speed[2]);
    geometry_msgs::msg::Twist get_CarTwist();
    std_msgs::msg::Float64 get_power();
    nav_msgs::msg::Odometry get_odom();
  /*  UPLOAD_STATUS car_status;*/

  private:
    //Wheel separation, wrt the midpoint of the wheel width: meters
    double wheel_separation;

    //Wheel radius (assuming it's the same for the left and right wheels):meters
    double wheel_radius;

    geometry_msgs::msg::Pose2D CarPos2D; // 小车开始启动原点坐标系
    geometry_msgs::msg::Twist CarTwist;  // 小车自身坐标系
    std_msgs::msg::Float64 CarPower;     // 小车电池信息
    nav_msgs::msg::Odometry CarOdom;     // 小车位置和速度信息
    //ros::NodeHandle mNH;
    //ros::Publisher mPose2DPub;
    //ros::Publisher mTwistPub;
    //ros::Publisher mStatusFlagPub;
    //ros::Publisher mPowerPub;
    //ros::Publisher mOdomPub;
    //ros::Publisher pub_barpoint_cloud_;
    //ros::Publisher pub_clearpoint_cloud_;
   
    std::shared_ptr<rclcpp::Node> nodeHandler_;
    rclcpp::Publisher<geometry_msgs::msg::Pose2D>::SharedPtr mPose2DPub;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr mTwistPub;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr mStatusFlagPub;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr mPowerPub;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr mOdomPub;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_barpoint_cloud_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_clearpoint_cloud_;
    

    bool mbUpdated;

    //boost::mutex mMutex;
    std::mutex mMutex;
    rclcpp::Time base_time_;
    rclcpp::Time current_time;

    XQ4IO *sta_serial;
    XQ4IO::XQ4Frame* msg = 0;

    //ros::Publisher mIMUPub;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr mIMUPub;
    sensor_msgs::msg::Imu CarIMU;
};

} //namespace xqserial_server

#endif // STATUSPUBLISHER_H
