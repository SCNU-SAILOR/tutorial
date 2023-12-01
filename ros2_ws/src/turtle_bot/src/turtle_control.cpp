#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp" // 控制位姿所需要的类（消息类型）
#include "turtle_bot/turtle_control.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<velocity_controller_ros>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
