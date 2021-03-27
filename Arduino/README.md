# Arduino Notes (Very rough)

## Refences

- [rosserial Adruino Setup](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

## Setup serial permissions

Add your user to the `dialout` group to get permission to read/write from serial 

```
sudo adduser $(whoami) dialout
```

## Install arduino IDE

https://www.arduino.cc/en/software


## Install rosserial library

Use the Tools -> Manage Libraries way to install `rosserial` at version `0.7.9` seems both newer versions AND the generation coming from the rosserial repo is bad

# OLD ---------------------

## Install ros desktop

http://wiki.ros.org/Installation/Ubuntu

## Install ros serial

Use the following command and replace `<flavor>` with whatevery ROS flavor you used to install in previous step

```
sudo apt-get install ros-<flavor>-rosserial-arduino
sudo apt-get install ros-<flavor>-rosserial
```

TODO: Do we need both?

## Adding rospkg

Not 100% why I needed to do this maybe some conflict with conda. Probably will try without next time and hunt down bugs when not being lazy.

```
pip install --user rospkg
```

## Generating arduino libraries

### Navigate to libraries location

```
cd <sketchbook>/libraries
```

On ubuntu should be `~/Arduino/libraries` by default

### Remove old generations

Only if this has been done before

```
rm -rf ros_lib
```

### Generate libraries

```
rosrun rosserial_arduino make_libraries.py .
```