# ROS2 （Robot Operating System 2）学习环境确认与版本兼容性

## 一、当前 ROS2 环境检查

在终端中执行：

```
printenv | grep ROS
```

得到结果：

```
ROS_VERSION=2
ROS_PYTHON_VERSION=3
ROS_AUTOMATIC_DISCOVERY_RANGE=SUBNET
ROS_DISTRO=jazzy
```

这说明：ROS 版本已正确激活，使用的是 Python 3，网络发现设置正常，当前 ROS 发行版是 Jazzy（Ubuntu 24.04 官方推荐版本）

环境已经成功配置，可以直接使用。

## 二、跟随鱼香 ROS2 教程是否可行？（Ubuntu 24.04 + ROS2 Jazzy）

鱼香 ROS 的《ROS2 机器人开发从入门到实践》教程依赖环境如下：Ubuntu 22.04，ROS2 Humble

当前使用的是：Ubuntu 24.04，ROS2 Jazzy

可以正常学习，大部分内容完全兼容。
 Jazzy 和 Humble 同属 ROS2 主线版本，API 基本一致，约 90% 的课程内容可以直接跟随学习。

网站：https://www.bilibili.com/video/BV1GW42197Ck/

## 三、版本差异及影响分析

教程使用 Humble，包名前缀是：

```
ros-humble-*
```

而 Jazzy 应改为：

```
ros-jazzy-*
```

只需要将版本名前缀替换即可。

# ROS2Node学习

## 1. ROS2 里的 “Node” 到底是什么？

**在 ROS2 中，Node 不是“一个语言写的类”或“一个脚本”而已。
 Node 是机器人系统中的 \*最小功能单元\*。**

就像：摄像头驱动是一个 Node激光雷达是一个 Node，SLAM 是一个 Node，导航规划是一个 Node

也就是说，整个机器人系统，是一堆节点互相通信组成的。

学 ROS2，就是学一个机器人系统怎么由很多 Node 组合起来。

Python 写的 ROS2 节点，就是“真正的 Node”

写 Python 节点，就是写一个真实可参与机器人系统的功能模块，而不是做练习。

## 2. 为什么学 ROS2 要从 Python 节点开始？

原因很简单：

### Python 写 Node 最快、最简单、最容易入门

ROS2 的复杂度很高：topic、service、action、参数、rcl、DDS 等等。
 如果直接用 C++ 入门，会劝退一半人。

Python 语法简单，又不需要管内存分配。

### Python 节点和机器人实际运行结构是一致的

你写的 Python 节点虽然只是几十行，但它的运行方式：

被 ROS2 运行；注册在 ROS 图中、；能与其他节点通信；能被 `ros2 node list` 看到；能发布/订阅真实消息

这是机器人系统的最基本能力。

所以写 Python Node 不仅仅是写代码，而是在构建真实机器人系统的一部分。

### Python 节点能快速试验你的算法

SLAM 的前置数据处理

导航参数动态调整

视觉识别的推理节点

真正机器人项目里，**调试和逻辑控制常用 Python 写节点，驱动层才用 C++**。

# ROS2话题学习

## 1. 什么是 ROS2 的话题（Topic）？

ROS2 中的话题（Topic）就是节点之间传递消息的异步通信通道，用于处理机器人运行时的连续数据流，帮助系统模块化、解耦并支持多对多通信。

**话题 = 数据通道 / 信息广播频道**

- **节点（Node）** 可以向某个话题 **发布（Publish）** 数据
- 其他节点可以 **订阅（Subscribe）** 这个话题以接收数据
- 发布者与订阅者 **彼此不需要认识对方**，只需要用同一个话题名字即可通信

因此，Topic 就像一个“广播电台频道”。

📡 谁向频道发消息 → 所有人都能听
 📡 多个订阅者也可以同时听同一个话题

## 2. 话题有什么作用？

### **1. 实现不同节点之间的数据传输**

例如：

- 激光雷达节点向 `/scan` 话题发布激光数据
- SLAM 节点订阅 `/scan`，用来建图
- 可视化工具 RViz 也订阅 `/scan`，用来显示模型

话题是**多对多通信机制**，非常灵活。

### **2. 实现模块化与解耦**

- 发布者不关心订阅者是否存在
- 订阅者也不关心是谁发的数据

这样你可以随时替换激光雷达、深度相机等节点，而无需修改其他代码。

这是 ROS2 强大、可扩展的关键原因。

### **3. 异步通信**

话题是**实时发送实时接收**，不需要等待对方回应。

适合：

- 传感器数据（激光、里程计、IMU、图像）
- 控制命令（速度指令）
- 状态反馈（电池、电机状态）

### **4. 话题是“流式数据”**

话题适合那种 **不断产生数据** 的情况：

例如：相机 30FPS：不断发送图像IMU：100Hz 发布角速度加速度 激光雷达：10Hz 发布点云

## 3. 话题包含哪些内容？ 

一个话题由三部分定义：

| 组成         | 说明                                                  |
| ------------ | ----------------------------------------------------- |
| **话题名称** | 例如 `/cmd_vel`、`/image_raw`                         |
| **消息类型** | `geometry_msgs/msg/Twist`、`sensor_msgs/msg/Image` 等 |
| **QoS 设置** | 可靠性、队列大小等（ROS2 新增特性）                   |

在发布/订阅时必须保证：
 **订阅者的消息类型要与发布者一致**

```
witcher@oslab:/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1$ ros2 run turtlesim turtlesim_node 
[INFO] [1763864129.882812313] [turtlesim]: Starting turtlesim with node name /turtlesim
[INFO] [1763864129.998754283] [turtlesim]: Spawning turtle [turtle1] at x=[5.544445], y=[5.544445], theta=[0.000000]

witcher@oslab:/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1$ ros2 node list
/turtlesim
witcher@oslab:/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1$ ros2 node info turtlesim
Unable to find node 'turtlesim'
witcher@oslab:/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1$ ros2 node info /turtlesim
/turtlesim
  Subscribers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /turtle1/cmd_vel: geometry_msgs/msg/Twist
  Publishers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /rosout: rcl_interfaces/msg/Log
    /turtle1/color_sensor: turtlesim/msg/Color
    /turtle1/pose: turtlesim/msg/Pose
  Service Servers:
    /clear: std_srvs/srv/Empty
    /kill: turtlesim/srv/Kill
    /reset: std_srvs/srv/Empty
    /spawn: turtlesim/srv/Spawn
    /turtle1/set_pen: turtlesim/srv/SetPen
    /turtle1/teleport_absolute: turtlesim/srv/TeleportAbsolute
    /turtle1/teleport_relative: turtlesim/srv/TeleportRelative
    /turtlesim/describe_parameters: rcl_interfaces/srv/DescribeParameters
    /turtlesim/get_parameter_types: rcl_interfaces/srv/GetParameterTypes
    /turtlesim/get_parameters: rcl_interfaces/srv/GetParameters
    /turtlesim/get_type_description: type_description_interfaces/srv/GetTypeDescription
    /turtlesim/list_parameters: rcl_interfaces/srv/ListParameters
    /turtlesim/set_parameters: rcl_interfaces/srv/SetParameters
    /turtlesim/set_parameters_atomically: rcl_interfaces/srv/SetParametersAtomically
  Service Clients:

  Action Servers:
    /turtle1/rotate_absolute: turtlesim/action/RotateAbsolute
  Action Clients:
```

### 使用命令行持续发布话题

```
ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0}, angular: {z: 1.0}}"
```

后面双引号内容的格式是yaml，冒号之后加空格，不同层级要加{}