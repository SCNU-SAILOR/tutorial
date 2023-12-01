#include <iostream>
using namespace std;
int main()
{
    int velocity_x = 0; // 初始化：速度初始为0

    velocity_x = velocity_x + 1;                // 加速代码
    cout << "一次加速：" << velocity_x << '\n'; // 可视化计算结果

    velocity_x = velocity_x + 1;                // 加速代码
    cout << "二次加速：" << velocity_x << '\n'; // 可视化计算结果

    velocity_x = velocity_x - velocity_x; // 急停代码
    cout << velocity_x << '\n';           // 可视化计算结果
    return 0;
}
