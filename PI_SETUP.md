# Pi Setup Notes

## Install ubuntu 20 on raspberry pi 

https://ubuntu.com/download/raspberry-pi

NOTE: Default login should be `ubuntu` with password `ubuntu`

## Connect pi to wifi

https://linuxconfig.org/ubuntu-20-04-connect-to-wifi-from-command-line

## SSH from desktop

```
ssh ubuntu@fermi.lan
```

NOTE: Not sure why `.local` didn't worked

## Install ROS noetic

Use the "bare bones" version

http://wiki.ros.org/noetic/Installation/Ubuntu


## Create a catkin workspace

http://wiki.ros.org/catkin/Tutorials/create_a_workspace

## Get Ferm-pi package

```
cd ~
https://github.com/CarterFendley/Fermi.git
ln -s /home/ubuntu/Fermi/fermi_pi /home/ubuntu/catkin_ws/src/fermi_pi
```

## Install fermi_pi packages

```
cd ~/catkin_ws
rosdep install --from-paths src --ignore-src -r -y
```

## Make the workspace

```
catkin_make
```

## Add the user to the tty group

```
sudo usermod -a -G tty $(whoami)
```

## Launch fermi packages

```
source devel/setup.bash
roslaunch fermi_pi fermi.launch
```