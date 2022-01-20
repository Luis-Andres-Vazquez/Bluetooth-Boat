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

                                                                            // **PRIMARY**

// Joystick Input
int VRx = A1;
int VRy = A2;

String horiz = "VRX";
String vert = "VRY";

                                                                       
void setup() {
  Serial.begin(9600); // Communication rate of bluetooth module
}

void loop() {
  VRx = analogRead(VRx); //Getting the values of the joystick position
  VRy = analogRead(VRy);
  //sending values to other slave
  Serial.println(horiz+VRx);
  Serial.println(vert+VRy);

  
}