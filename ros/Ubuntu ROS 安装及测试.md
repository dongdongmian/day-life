### Ubuntu ROS 安装及测试

[TOC]

[参考原址](http://wiki.ros.org/kinetic/Installation/Ubuntu)

#### 安装

1. **更新源列表**
		sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

2. **取得 key**
		sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

3. **安装**
		sudo apt-get update
        
        sudo apt-get install ros-kinetic-desktop-full
        //sudo apt-get install ros-kinetic-desktop
        //sudo apt-get install ros-kinetic-ros-base
        //sudo apt-get install ros-kinetic-PACKAGE
        //sudo apt-get install ros-kinetic-slam-gmapping
        
        //获取 ros 包目录:
        apt-cache search ros-kinetic

4. **初始化 rosdep**
rosdep 使您能够轻松地为要编译的源安装系统依赖项，并且需要在ROS中运行一些核心组件。
		sudo rosdep init
		rosdep update

5. 环境配置
环境变量自动更新到 bash 会话中
		echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
		source ~/.bashrc

6. 安装 rosinstall
rosinstall 是 ROS 中的命令行工具,是单独发行的.它能够使用一个命令轻松下载ROS 软件包的许多源代码树依赖.
		sudo apt-get install python-rosinstall
