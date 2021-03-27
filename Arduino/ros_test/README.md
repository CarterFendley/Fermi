# Give it a test

## Start roscore

```
roscore
```

## Start serial node

```
rosrun rosserial_python serial_node.py /dev/ttyUSB0
```

NOTE: If using conda might have to `conda deactivate` before running this


## Push values to the two topics

```
rostopic pub -1 left_pwm std_msgs/Int16 -- 255
```

```
rostopic pub -1 right_pwm std_msgs/Int16 -- 255
```