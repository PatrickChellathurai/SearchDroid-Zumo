# SearchDroid-Zumo
Search Droid Robot

Search Droid Assignment with Zumo Robot

Objective 
 Aim is to Program a Zumo pololu Robot to use as a Search Droid to search for an object or a person in the room inside the building. It should be able to go along a corridor and turns right or left in the corners then enters into the rooms and checks for a person or an object then finally returns to the base.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Important Note
The code for Robot has be adapted so it will work on a faulty Zumo Robot. As the testing Robot goes toward left slightly when its programed to go straight.  
I.e:   To go forward its meant to be  motors.setSpeeds(200, 200);  but its been set like below:
(  motors.setSpeeds(200, -187);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Items Used/Needed

•	Zumo Robot
•	Arduino board
•	Xbee modules 
•	Ultrasonic sensor 


Libraries Used

ZumoMotors.h
Pushbutton.h
QTRSensors.h
ZumoReflectanceSensorArray.h
SoftwareSerial.h
NewPing.h


Programing strategy 

The idea is that the robot will 
•	turn 30 degrees to the Right and goes forward for 3-5 cm then checks for a black line. Then changes the variable for right line to 1  
•	Then come back to the start position by reversing back and turns Left 30 degrees.
•	Once its straight then it will check for the lines on the left. Then sets another variable for left 
•	if both lines exists then the robot will go forward and if right is set to zero and left is set to 1 then its turns right, likewise the left turn operates similarly.
•	If both are zero, it will mean the robot has detected a room and goes inside and scans for an object.
•	There are also variables that identifies when its enter a room on the right or left so it can comes out and continues to go forward on the corridor.
•	If it turn into a room on the left it will comes out  and turns left and If its turn into a room on the right  the robot  will come out  and turns Right  
•	When it senses a black line below it will reverse and turns around. 

A pair of Xbee has been used with to communicate its current state to a laptop running XTCU Utility.


