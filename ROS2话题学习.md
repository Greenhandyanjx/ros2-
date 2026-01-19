## ROS2话题学习

![image-20251201091216832](D:\Typora\images\image-20251201091216832.png)

使用python中psutils获取对应的小车运行时的系统信息，使用话题发布对应的内容，再用c++进行订阅然后使用c++展示对应的信息。

1、自定义通信接口

![image-20251201091509334](D:\Typora\images\image-20251201091509334.png)

ROS2中没有对应信息的接口，我们需要自定义。

![image-20251201092805950](D:\Typora\images\image-20251201092805950.png)

比如这个时候把依赖填错了怎么办：

![image-20251201093010359](D:\Typora\images\image-20251201093010359.png)

不能直接使用相同的命令进行操作

ros2 pkg create status_interfaces --dependencies builtin_interfaces rosidl_default_generators --license Apache-2.0

包已经存在，不能直接这么向包中导入依赖和license

需要删除操作：rm -rf status_interfaces

再重新构建

包中的builtin_interfaces:用来提取时间戳

rosidl_default_generators：可以把我们的自定义消息文件转换为c++、python的源码

创建成功之后的工作空间目录：

![image-20251201093550558](D:\Typora\images\image-20251201093550558.png)

然后在对应的文件夹中添加对应的消息接口（使用大驼峰命名法）

![image-20251201094201086](D:\Typora\images\image-20251201094201086.png)

builtin_interfaces/Time stamp
string host_name
float32 cpu_percent
float32 memory_percent
float32 memory_total
float32 memory_available
float64 net_sent
float64 net_recv

信息接口定义完之后：

![image-20251201094708386](D:\Typora\images\image-20251201094708386.png)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SystemStatus.msg"
  DEPENDENCIES builtin_interfaces
)

最后到对应文件中添加：

![image-20251201094948426](D:\Typora\images\image-20251201094948426.png)

 <member_of_group>rosidl_interface_packages</member_of_group>

告诉系统这是一个带着消息接口的功能包

然后进行构建：

![image-20251201095318832](D:\Typora\images\image-20251201095318832.png)

构建需要回到项目所在的总文件夹

witcher@oslab:/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1/chap3/practice_ws$ colcon build

生成后项目文件：项目目录

![image-20251201100127667](D:\Typora\images\image-20251201100127667.png)

c++：![image-20251201095828948](D:\Typora\images\image-20251201095828948.png)

python：

![image-20251201100100676](D:\Typora\images\image-20251201100100676.png)

成功定义了消息接口，就可以使用消息接口进行话题的发布了

![image-20251201100744231](D:\Typora\images\image-20251201100744231.png)

在对应的文件夹中编写发布的节点代码：

![image-20251201103253181](D:\Typora\images\image-20251201103253181.png)

```
import rclpy
from rclpy.node import Node
from status_interfaces.msg import SystemStatus
import psutil
import platform

class SysStatusPub(Node):
    def __init__(self, node_name):
        self.status_publisher_ = self.create_publisher(
            SystemStatus, 'sys_status',10
        )
        self.timer_ =self.create_timer(1.0,self.time_callback)
    def time_callback(self):

        cpu_percent = psutil.cpu_percent()                                                                                                                                                                              
        memoryinfo= psutil.virtual_memory()
        net_io_counters = psutil.net_io_counters()
        msg=SystemStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.host_name = platform.node()
        msg.cpu_percent=cpu_percent
        msg.memory_percent= memoryinfo.percent
        msg.memory_total=memoryinfo.total
        msg.memory_available=memoryinfo.available/1024/1024
        msg.net_sent=net_io_counters.bytes_sent/1024/1024
        msg.net_recv=net_io_counters.bytes_recv/1024/1024
    
        self.get_logger().info(f'pub: {str(msg)}')
        self.status_publisher_.publish(msg)

def main():
    rclpy.init()
    node = SysStatusPub('sys_status_pub')
    rclpy.spin(node)
    rclpy.shutdown()
```

编写完代码之后在setup中填写以把它变成可执行文件

![image-20251201103739266](D:\Typora\images\image-20251201103739266.png)

    entry_points={
        'console_scripts': [
            'sys_status_pub= status_publisher.sys_status_pub:main',
        ],
    },

![image-20251201104006110](D:\Typora\images\image-20251201104006110.png)

最后回到项目的根目录再次进行colcon build，可以找到对应的可执行文件

进行对应的运行：

![image-20251201104405124](D:\Typora\images\image-20251201104405124.png)

发现报了缺少对应属性的错误，发现错误是因为在init中没有super调用父类的初始化函数

在sysStatusPub中添加super().__init__(node_name)

就OK了

运行节点：

![image-20251201110412244](D:\Typora\images\image-20251201110412244.png)

发现只运行一次报错了，错误的原因是memorytotal忘了/1024/1024数字太大，超float32范围了

运行节点命令

colcon build

source install/setup.bash

ros2 run status_publisher sys_status_pub

![image-20251201110644740](D:\Typora\images\image-20251201110644740.png)

正确打印对应的属性。

此时打开另一个终端进行echo（这个命令用于查看并显示 /sys_status 话题上发布的消息内容。它会输出该话题的实时消息流。）

![image-20251201111322252](D:\Typora\images\image-20251201111322252.png)

此时报错：

![image-20251201111239021](D:\Typora\images\image-20251201111239021.png)

需要source install/setup.bash （这个命令是用来加载工作空间的环境变量。每当你构建 ROS 2 工作空间时，需要运行此命令来设置环境变量，使得 ROS 2 系统可以识别工作空间中的包和消息类型。使你能够使用当前工作空间中构建的包，确保 ROS 2 运行时能够找到相应的包和消息类型。）

然后重新echo就行了

ROS 2 是一个 异步通信系统，一个终端负责发布消息，另一个终端则负责接收和显示这些消息。

这里的run作为一个发布者，echo作为一个订阅者

作为订阅者的电脑必须编译然后拥有interfaces消息接口，那如果没有进行订阅的话会显示无法echo，因为传的是二进制流，是根据接口的定义进行编译的。