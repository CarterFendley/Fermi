#define ML_Ctrl 13  // define the direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define the direction control pin of right motor
#define MR_PWM 3    //define PWM control pin of right motor

void setup() {
  Serial.begin(115200);

  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
}

void loop() {
  char sb = NULL;
  char command = NULL;
  if (Serial.available()){
    sb = Serial.read();

    if(sb != 0xA){
      command = sb;
    }
  }

  if (command == 'f' || command == 'F'){
    tank_drive(255, 255);
  }
  else if (command == 'b' || command == 'B'){
    tank_drive(-255, -255);
  }
  else if (command == 'r' || command == 'R'){
    tank_drive(-255, 255);
  }
  else if (command == 'l' || command == 'L'){
    tank_drive(255, -225);
  }
  else if (command == 's' || command == 'S'){
    tank_drive(0, 0);
  }

  delay(5);
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
