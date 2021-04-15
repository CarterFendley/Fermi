#!/usr/bin/env python3
import math
import rospy
from std_msgs.msg import Int16
from sensor_msgs.msg import Joy
from numpy import interp
import threading

Y_AXIS = 1
X_AXIS = 2

def square(x, y):
    return math.copysign(x**2, x), math.copysign(y**2, y)

def arcade_drive(x, y, max_pwm=255, turn_power=0.5, square_inputs=True):
    if square_inputs:
        x, y = square(x, y)
    
    max_power = 1 + turn_power

    # Map from joysticks to left / right motor power
    left_pwm = int(interp(y - (x*turn_power), [-max_power, max_power], [-max_pwm,max_pwm]))
    right_pwm = int(interp(y + (x*turn_power), [-max_power, max_power], [-max_pwm,max_pwm]))

    return left_pwm, right_pwm

class Teleop:

    def __init__(self, rate=10.0, verbose=False):
        rospy.init_node('teleop', anonymous=True)

        # Ros publisher
        self.left_pub = rospy.Publisher('/left_pwm', Int16, queue_size=2)
        self.right_pub = rospy.Publisher('/right_pwm', Int16, queue_size=2)

        self.left_pwm = 0
        self.right_pwm = 0

        self.cv = threading.Condition()

        # Publishing rate
        if rate != 0.0:
            self.timeout = 1.0 / rate
        else:
            self.timeout = None

        self.verbose = verbose

    def joy_callback(self, data):
        x = data.axes[X_AXIS]
        y = data.axes[Y_AXIS]

        if self.verbose:
            rospy.loginfo(f'TELEOP: Got joystick (x: {x}, y: {y})')

        # Update the pwm values
        self.cv.acquire()

        self.left_pwm, self.right_pwm = arcade_drive(x, y)

        if self.verbose:
            rospy.loginfo(f'TELEOP: Set (left: {self.left_pwm}, right: {self.right_pwm})')

        self.cv.notify()
        self.cv.release()
    

    def run(self):
        rospy.Subscriber('/joy', Joy, self.joy_callback)

        while not rospy.is_shutdown():
            self.cv.acquire()

            left_pwm = 0
            right_pwm = 0

            # Wait for some time to allow for joy update / otherwise send zero-ed values
            self.cv.wait(self.timeout)
            
            left_pwm = self.left_pwm
            right_pwm = self.right_pwm
            # Reset set values as default for next iter
            self.left_pwm = 0
            self.right_pwm = 0

            self.cv.release()
            
            self.left_pub.publish(left_pwm)
            self.right_pub.publish(right_pwm)

        

if __name__ == '__main__':
    try:
        teleop = Teleop()
        teleop.run()
    except rospy.ROSInterruptException:
        pass
    