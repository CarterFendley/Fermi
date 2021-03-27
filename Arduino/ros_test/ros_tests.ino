#include <ros.h>
#include <std_msgs/Int16.h>

ros::NodeHandle nh;

#define ML_Ctrl 13  // define the direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define the direction control pin of right motor
#define MR_PWM 3    //define PWM control pin of right motor

int16_t right = 0;
int16_t left = 0;

void rightCallBack(const std_msgs::Int16& r){
  right = r.data;
}

void leftCallBack(const std_msgs::Int16& l){
  left = l.data;
}

ros::Subscriber<std_msgs::Int16> subRight("right_pwm", &rightCallBack);
ros::Subscriber<std_msgs::Int16> subLeft("left_pwm", &leftCallBack);

void setup()
{ 
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  
  nh.initNode();
  nh.subscribe(subRight);
  nh.subscribe(subLeft);
}

void loop()
{  
  nh.spinOnce(); // Listen for updates

  tank_drive(right, left);
  
  delay(1);
}

void tank_drive(int right, int left){

  // Set direction of motors
  if(right < 0){
    digitalWrite(MR_Ctrl, HIGH);
    right *= -1;
  }else{
    digitalWrite(MR_Ctrl, LOW);
  }
  if(left < 0){
    digitalWrite(ML_Ctrl, HIGH);
    left *= -1;
  }else{
    digitalWrite(ML_Ctrl, LOW);
  }

  // Apply bounds
  right = min(right, 255);
  left  = min(left, 255);

  // Send PWM signal
  analogWrite(MR_PWM, right);
  analogWrite(ML_PWM, left);
}
