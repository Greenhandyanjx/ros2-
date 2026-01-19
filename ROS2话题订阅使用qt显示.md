### ROS2话题订阅使用qt显示

还是一样的新建一个包，使用的依赖是ros2中的rclcpp 和我们刚才已经定义好的消息订阅接口。

![image-20251208094537537](D:\Typora\images\image-20251208094537537.png)

```c++
#include <QApplication>
#include <QLabel>
#include <QString>
#include "rclcpp/rclcpp.hpp"
#include "status_interfaces/msg/system_status.hpp"

using SystemStatus = status_interfaces::msg::SystemStatus;

class SysStatusDisplay : public rclcpp::Node {
 public:
  SysStatusDisplay() : Node("sys_status_display") {
    subscription_ = this->create_subscription<SystemStatus>(
        "sys_status", 10, [&](const SystemStatus::SharedPtr msg) -> void {
          label_->setText(get_qstr_from_msg(msg));
        }); 
  	// 创建一个空的 SystemStatus 对象，转化成 QString 进行显示
    label_ = new QLabel(get_qstr_from_msg(std::make_shared<SystemStatus>()));
    label_->show();
  }
QString get_qstr_from_msg(const SystemStatus::SharedPtr msg) {
    std::stringstream show_str;
    show_str
        << "===========系统状态可视化显示工具============\n"
        << "数 据 时 间:\t" << msg->stamp.sec << "\ts\n"
        << "用  户  名:\t" << msg->host_name << "\t\n"
        << "CPU使用率:\t" << msg->cpu_percent << "\t%\n"
        << "内存使用率:\t" << msg->memory_percent << "\t%\n"
        << "内存总大小:\t" << msg->memory_total << "\tMB\n"
        << "剩余有效内存:\t" << msg->memory_available << "\tMB\n"
        << "网络发送量:\t" << msg->net_sent << "\tMB\n"
        << "网络接收量:\t" << msg->net_recv << "\tMB\n"
        << "==========================================";

    return QString::fromStdString(show_str.str());

  }


 private:
  rclcpp::Subscription<SystemStatus>::SharedPtr subscription_;
  QLabel* label_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  QApplication app(argc, argv);
  auto node = std::make_shared<SysStatusDisplay>();
  std::thread spin_thread([&]() -> void { rclcpp::spin(node); });
  spin_thread.detach();
  app.exec();
  rclcpp::shutdown();
  return 0;
}
```

这个时候我们编写完节点之后，要怎么调用对应的qt显示逻辑呢

![image-20251208095109495](D:\Typora\images\image-20251208095109495.png)

如果直接只是有一个main函数创建的进程的话，spin会阻塞代码，app.exec也会阻塞代码，怎么办？

使用多进程同时运行

![image-20251208094914594](D:\Typora\images\image-20251208094914594.png)

编写完代码之后：

需要到cmakelist中添加对应的可执行文件

![image-20251208095623391](D:\Typora\images\image-20251208095623391.png)

最后就是进行colcon build：

![image-20251208100047543](D:\Typora\images\image-20251208100047543.png)

`CMakeLists.txt` 中使用了 `target_link_libraries(... Qt5::Widgets)`，但是 没有正确 find_package(Qt5 COMPONENTS Widgets)。

需要在cmakelist中添加find_package(Qt5 COMPONENTS Widgets)

![image-20251208100243876](D:\Typora\images\image-20251208100243876.png)

CMakeLists.txt添加可执行文件：

```
find_package(Qt5 REQUIRED COMPONENTS Widgets)
add_executable(sys_status_display src/sys_status_display.cpp)
target_link_libraries(sys_status_display Qt5::Widgets) # 对于非ROS功能包使用Cmake原生指令进行链接库
ament_target_dependencies(sys_status_display rclcpp status_interfaces)

install(TARGETS sys_status_display
  DESTINATION lib/${PROJECT_NAME})
```

![image-20251208100735094](D:\Typora\images\image-20251208100735094.png)

![image-20251208100935176](D:\Typora\images\image-20251208100935176.png)