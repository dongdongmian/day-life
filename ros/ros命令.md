### ros 命令

[TOC]

#### 新建工作环境
src: catkin_init_workspace
catkin_make
source devel/setup.bash

新建 package:
`catkin_create_pkg <package_name> [depend_1] ... [depend_n]`
	`catkin_create_pkg beginner_tutorials std_msgs rospy roscpp`