# Robot_tank
A smart car based on ROS.
### 项目目标设计
在arm架构的开发板上以ROS为平台，实现具有以下功能的小车\:
  - 自主导航与避障
  - 物体识别与定位
  - 语音控制/交互
  - 对被识别物体的抓取
### 项目实现方案
1. 材料
  - 履带底盘，42步进电机，6自由度机械臂
  - Firefly RK3399开发板，Arduino mega2560, 
  - 杉川激光雷达A0602，乐视Xtion Pro RGB摄像头
  - 524V电源，变压模块，继电器，usb转串口模块，面包板
2. 实现方案
  - 电机未采用直流电机，未使用闭环控制\(如能不失步，可确保足够的精确度\)。
  - 控制电机的流程为：Firefly开发板\(ROS\)\-Arduino\-步进电机驱动器\-步进电机。
    其中，Arduino上的程序可以实现在同时只有一组脉冲时，驱动两电机有不同的速度。
    详见[点击](https://www.zhihu.com/question/52708719/answer/585089570)
  - 里程计的数据由一个python程序监听cmd_vel，geometry_msgs/Twist主题的广播，相应变换为odom主题所需格式后广播。
  - 在odom主题可以成功发布的情况下，用雷达gmapping建图(室内)如下：
  ![map](https://github.com/Dennis-lixinze/Robot_tank/raw/master/display/map.JPG?imageMogr2/auto-orient/strip%7CimageView2/2/w/300)
  
