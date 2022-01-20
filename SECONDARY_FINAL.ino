/* THIS IS THE FINAL CODE FOR THE BLUETOOTH CONTROLLED BOAT USING THE FOLLOWING: 

 SECONDARY: ARDUINO NANO, BLUETOOTH HC-05, L298N H-BRIDGE MOTOR CONTROLLER (NEED 9V BATTERY), 2 YELLOW DC MOTORS (ALSO TO POWER ARDUINO NANO NEEDS ANOTHER 4.5V BATTERY - 3 AA) 

 PRIMARY: ARDUINO UNO, BLUETOOTH HC-05, JOYSTICK
   
 GOAL & PLAN:
PRIMARY: THE ARDUINO UNO WILL BE CONNECTED TO THE COMPUTER (POWERING IT), THE BLUETOOTH MODULE WILL SEND THE JOYSTICK VALUES (VRY,VRX ) TO THE OTHER BLUETOOTH 
MODULE ON THE SECONDARY  BY WRITING THE VALUES TO THE SERIAL MONITOR.
 
SECONDARY: THESE COMPONENTS WILL SIT ON THE BOAT. THE SLAVE BLUETOOTH MODULE WILL RECEIVE THE VALUES AND GIVE THEM TO THE ARDUINO NANO WHICH HAS BEEN PROGRAMMED TO ACT ACCORDING TO THE VALUES. 
THE VALUES WILL CORRESPOND TO HOW THE MOTOR CONTROLLER REACTS AND CONTROLS THE MOTORS. 

NOTE: THE BLUETOOTH MODULES CAN COMMUNICATE WITHIN 10 METERS
*/

                                                                               // **SECONDARY**
//Setting up motors
//Motor A
int enA = 9; // Enable (allows motor A to run) (Must be a pin possible of PWM (~))
int in1 = 8; // the way an H-bridge works, rotation direction according to two inputs
int in2 = 7;

// Motor B

int enB = 3; //(PWM)
int in3 = 5;
int in4 = 4;

int MotorSpeedA = 0;
int MotorSpeedB = 0;

// Joystick Input
long VRx = 512;
long VRy = 512;

// Loop Variables
char valIndi[4] = "VRY";  // value indicator has 3 letters



void setup() {

  //L298N Setup
  pinMode(enA,OUTPUT); 
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //Motors setup

  //Motor A: don't run but set direction
  digitalWrite(enA,LOW);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  //Motor B
  digitalWrite(enB,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  //Bluetooth setup
  Serial.begin(9600); // since the bluetooth module communicates at a baud rate of 9600 (bits per second)

}

void loop() {
  if(Serial.available()>0){
    //To read from serial monitor what the value we receive is for, VRY, VRX?
    //On the serial monitor any data transfered will have its indicator first as 3 characters
    //followed immediately by its value and ends. e.g: VRY989, VRX1023

    Serial.readBytesUntil('\n',valIndi,3);


    if(strcmp(valIndi,"VRX") == 0){

      //The next lines gives Vrx the number value in the serial monitor
      VRx = Serial.parseInt(SKIP_ALL,'\n'); //parseInt looks for numbers and ignores other things

    } else{
        VRy = Serial.parseInt(SKIP_ALL, '\n');    

    } 
  }

  //Controlling the motors according to the joystick position VRy and VRx

  // Checking if backward or forward

  if (VRy < 400){

    //Set motors backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    //  Motor speeds
    //  revesring readings
    VRy = VRy - 400; //Produces negative number
    VRy = VRy * -1;  // Make number +ve (this works because the bottom half of the joystick means go back,
                     // the further from the middle the faster it goes backward

    MotorSpeedA = map(VRy, 0, 400, 0, 255); // converts the scale of the joystick (0-460 here) to the scale of the motor (0-255)
    MotorSpeedB = map(VRy, 0, 400, 0, 255);
  }
  else if (VRy > 600)
  {

    //Forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    //Motor speeds
    MotorSpeedA = map(VRy, 600, 1023, 0, 255);
    MotorSpeedB = map(VRx, 600, 1023, 0, 255);
  }
  else
  {
    MotorSpeedA = 0;
    MotorSpeedB = 0;
  }

  // Turning, LEFT AND RIGHT (Motor B on the right and A on the left)

  if (VRx < 400){ //LEFT
    VRx = VRx - 400;
    VRx = VRx * -1;


    //Value according to speed
    VRx = map(VRx, 0, 400, 0 ,255);
    

    // The difference in motor speed to turn 
    MotorSpeedA = MotorSpeedA - VRx;
    MotorSpeedB = MotorSpeedB + VRx; 

  

    // To not exceed 0-255 range 

    if (MotorSpeedA < 0) MotorSpeedA =0;
    if (MotorSpeedB > 255) MotorSpeedB =255;

  //    Serial.println("Made it here too");
  }

  else if (VRx > 600){ //RIGHT
    VRx = map(VRx, 600, 1023, 0, 255); 

    MotorSpeedA = MotorSpeedA + VRx;
    MotorSpeedB = MotorSpeedB - VRx;
    //Not exceeding

    if (MotorSpeedA > 255) MotorSpeedA = 255;
    if (MotorSpeedB < 0) MotorSpeedB = 0;
    
  }

    //To prevent Buzzing at low speeds

    if (MotorSpeedA < 25) MotorSpeedA = 0;
    if (MotorSpeedB < 25) MotorSpeedB = 0;

  //setting motor speed finally'

    analogWrite(enA, MotorSpeedA);
    analogWrite(enB, MotorSpeedB);

} 
