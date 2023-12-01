
#include <iostream>
using namespace std;

class velocity_controller
{
public:
    int velocity_x; // 这里声明了一个公有的整型变量velocity_x，用于表示速度
    velocity()      // 下面是默认构造函数
    {
        velocity_x = 0; // 在构造函数中，我们将速度初始化为0
    }
    void speed_up() // 这是一个成员函数，用于加速操作
    {
        velocity_x = velocity_x + 2; // 加速操作，将速度增加2
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

int main()
{
    velocity_controller robot_velocity = velocity(); // 初始化机器人速度对象

    robot_velocity.speed_up();         // 机器人加速
    robot_velocity.display_velocity(); // 可视化计算结果

    robot_velocity.speed_up();         // 机器人再次加速
    robot_velocity.display_velocity(); // 可视化计算结果

    robot_velocity.stop();             // 机器人急停
    robot_velocity.display_velocity(); // 可视化计算结果

    return 0;
}
