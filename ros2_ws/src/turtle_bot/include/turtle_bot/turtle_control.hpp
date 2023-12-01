#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp" // 控制速度所需要的类（消息类型）
#include <iostream>
using namespace std;
class velocity_controller
{
public:
    int velocity_x;       // 这里声明了一个公有的整型变量velocity_x，用于表示速度
    velocity_controller() // 下面是默认构造函数
    {
        velocity_x = 0; // 在构造函数中，我们将速度初始化为0
    }
    void speed_up() // 这是一个成员函数，用于加速操作
    {
        velocity_x = velocity_x + 1; // 加速操作，将速度增加2
    }
    void stop() // 这是另一个成员函数，用于急停操作
    {
        velocity_x = velocity_x - velocity_x; // 急停操作，将速度归零
    }
    void display_velocity() // 这是用于显示速度的成员函数
    {
        cout << velocity_x << '\n'; // 显示当前速度
    }
};

class new_velocity_controller : public velocity_controller
{
public:
    new_velocity_controller() : velocity_controller(){};

    void enter_lightspeed()
    {
        velocity_x = 299792458;
    }
};

class velocity_controller_ros : public rclcpp::Node, public new_velocity_controller
{
public:
    velocity_controller_ros()
        : Node("turtle_velocity_publisher"), new_velocity_controller() // 结点的名称
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        speed_up_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&velocity_controller_ros::speed_up_demo, this));
        stop_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(2000),
            std::bind(&velocity_controller_ros::stop_demo, this));
    }

private:
    void speed_up_demo()
    {
        this->speed_up();
        this->publish_velocity();
    }

    void stop_demo()
    {
        stop();
        publish_velocity();
    }

    void
    publish_velocity()
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = velocity_x;
        RCLCPP_WARN(this->get_logger(),
                    "Publishing velocity command: linear_x: '%.2f'", message.linear.x);
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr speed_up_timer_;
    rclcpp::TimerBase::SharedPtr stop_timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};