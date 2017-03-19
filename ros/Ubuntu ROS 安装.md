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

#### 测试

##### 创建 ROS 工作环境

**catkin工作环境**
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace

//build
cd ~/catkin_ws/
catkin_make
```
创建后,在文件夹内有两个文件夹:build & devel
devel 存放配置文件
在配置完成后确定你的工作目录在 ROS_PACKAGE_PATH 中
		echo $ROS_PACKAGE_PATH

###### catkin overview
catkin 是 ROS 官方的构建系统.catkin 和 rosbuild 结合了CMake宏和Python脚本,在CMake的正常工作流程之上提供一些功能.

'CMakeLists.txt' 是 catkin 的编译规则文件

**package.xml**
1. catkin工作区中catkin-packages的配置步骤（cmake）序列的排序
2. 定义 bloom 的包装依赖关系（在创建 debian pkg 时要导出的依赖关系）
3. 定义 rosdep 的系统（非 catkin-pkgs）构建依赖项
4. roswiki / graph 工具的构建或安装或运行时依赖性文档（rqt_graph）



``` html
<package>
  ...
  <name>example_pkg</name>
  <buildtool_depend>catkin</buildtool_depend>
  <build_depend>cpp_common</build_depend>
  <build_depend>log4cxx</build_depend>
  <test_depend>gtest<test_depend>
...
  <run_depend>cpp_common</run_depend>
  <run_depend>log4cxx</run_depend>
<package>
```

**CMakeLists.txt**
准备和执行构建过程
```
find_package(catkin REQUIRED COMPONENTS cpp_common geometry_msgs)
find_package(Log4cxx QUIET)
generate_messages(DEPENDENCIES geometry_msgs)
catkin_package(
  CATKIN_DEPENDS cpp_common geometry_msgs
  DEPENDS Log4cxx
)
add_library(example_lib src/example.cpp)
target_link_libraries(example_lib ${catkin_LIBRARIES} ${LOG4CXX_LIBRARIES})
add_dependencies(example_lib geometry_msgs_gencpp)
```

