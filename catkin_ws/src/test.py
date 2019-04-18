#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 文件名：server.py
import rospy
from geometry_msgs.msg import Twist
import socket               # 导入 socket 模块
class OutAndBack():
    def __init__(self):
        rospy.init_node('out_and_back',anonymous=False)
        rospy.on_shutdown(self.shutdown)
        self.cmd_vel = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
        s = socket.socket()         # 创建 socket 对
     #   host = socket.gethostname()
        port = 8000              # 设置端口
        s.bind(('0.0.0.0', port))        # 绑定端口
        s.listen(5)                 # 等待客户端连
        while True:
            c, addr = s.accept()     # 建立客户端连接。
            print '连接地址：', addr
            while True:
               data = c.recv(512) # 1024个字s
               if not data:
                  break
               list1 = data.split(',')
               move_cmd = Twist()
               linear=list1[0]
               augular=list1[1]
               on =list1[2]
               print '1'
               Linear = float(linear)
               Angular=float(augular)
               ON = float(on)
               print '2'
               move_cmd.linear.x = Linear
               move_cmd.angular.z=Angular
               move_cmd.angular.x = ON
               self.cmd_vel.publish(move_cmd)
            c.close()                # 关闭连接
    def shutdown(self):
        # Always stop the robot when shutting down the node.
        rospy.loginfo("Stopping the robot...")
        self.cmd_vel.publish(Twist())
        rospy.sleep(1)
if __name__ == '__main__':
    try:
        OutAndBack()
    except:
        rospy.loginfo("Out-and-Back node terminated.") 
