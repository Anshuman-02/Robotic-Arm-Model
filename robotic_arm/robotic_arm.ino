//Quartz Mini Robotic ARM - Testing code  
//Joystick 1 and 2 is connected to A0,A1, A2 and A3
//SERVO CONNECTIONS
//Neck sero - D10 - pos is saved at EEPROM 3
//Front and Back - D11 - pos is saved at EEPROM 2
//UP and Down - D9 - pos is saved at EEPROM 1
//Gripper - D6 - pos is saved at EEPROM 0
//created by: Aswinth Raj
//created for: quartzcomponents.com
#include <Servo.h>
#include <EEPROM.h>
//All the gripper positions will be saved and read from eeprom to resume same positon
int gripper_pos = EEPROM.read(0);
int updown_pos = EEPROM.read(1);
int frontback_pos = EEPROM.read(2);
int neck_pos = EEPROM.read(3);
// Create a servo object - one each for 4 servos
Servo Gripper_servo;
Servo UpDown_servo;
Servo FrontBack_servo;
Servo Neck_servo;
//Function the control the servo based on joystick position
void control_servo (Servo &current_servo, int current_pos, int EEPROM_addr)
{
    //positon should alwasy be between 0 to 180
    if (current_pos>=180)
    current_pos=175; //jitter at maximum limit
    if (current_pos<=0)
    current_pos=10; //jitter at minimum limit
    current_servo.write(current_pos); //update servo postion
    EEPROM.write(EEPROM_addr, current_pos); //save position in EEPROM
    Serial.print(EEPROM_addr); Serial.print(" = "); Serial.println(current_pos); //for debugging on serial monitor
}
void setup() {
  Serial.begin (9600);
  Gripper_servo.attach(6);
  Gripper_servo.write(gripper_pos);
  UpDown_servo.attach(9);
  UpDown_servo.write(gripper_pos);
  FrontBack_servo.attach(11);
  FrontBack_servo.write(gripper_pos);
  Neck_servo.attach(10);
  Neck_servo.write(gripper_pos);
}
void loop() {
  /*//USE FOR DEBUGGING
  Serial.println ("Gripper, UpDown, FrontBack, Neck");
  Serial.print(gripper_pos);Serial.print(",");
  Serial.print(updown_pos);Serial.print(",");
  Serial.print(frontback_pos);Serial.print(",");
  Serial.print(neck_pos);Serial.println(".");*/
  delay(50); //predefined  delay to make the servo move slower
//A0 to control Gripper Servo
  int Joy_value_X1 = analogRead (A0);
  if (Joy_value_X1 > 700){
    gripper_pos = gripper_pos + 1;
    control_servo (Gripper_servo, gripper_pos, 0);
  }
  if (Joy_value_X1 < 300){
    gripper_pos = gripper_pos - 1;
    control_servo (Gripper_servo, gripper_pos, 0);
  }
//A1 to control UpDown Servo
    int Joy_value_Y1 = analogRead (A1);
  if (Joy_value_Y1 > 700){
    updown_pos = updown_pos + 1;
    control_servo (UpDown_servo, updown_pos, 1);
  }
  if (Joy_value_Y1 < 300){
    updown_pos = updown_pos - 1;
    control_servo (UpDown_servo, updown_pos, 1);
  }
//A2 to control FrontBack Servo
      int Joy_value_X2 = analogRead (A2);
  if (Joy_value_X2 > 700){
    frontback_pos = frontback_pos + 1;
    control_servo (FrontBack_servo, frontback_pos, 2);
  }
  if (Joy_value_X2 < 300){
    frontback_pos = frontback_pos - 1;
    control_servo (FrontBack_servo, frontback_pos, 2);
  }
//A3 to control Neck Servo
        int Joy_value_Y2 = analogRead (A3);
  if (Joy_value_Y2 > 700){
    neck_pos = neck_pos + 1;
    control_servo (Neck_servo, neck_pos, 3);
  }
  if (Joy_value_Y2 < 300){
    neck_pos = neck_pos - 1;
    control_servo (Neck_servo, neck_pos, 3);
  }
}
