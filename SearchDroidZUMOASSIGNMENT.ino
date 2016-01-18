#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <SoftwareSerial.h>
#include <NewPing.h>

 SoftwareSerial xbee(2, 3); 
#define LED 13

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1200 // microseconds
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     100 // 0 is stopped, 400 is full speed
#define TURN_SPEED        100
#define FORWARD_SPEED     70
#define REVERSE_DURATION  100 // ms
#define TURN_DURATION     100 // ms
#define forward 0
int Right_line = 0; // if there is line on the right side
int Left_line = 0; // if there is line on the right side
int Returningtobase = 0;
int Secondrightturn = 0;
int Rightroom = 0;// Indentifies if the Right Room
int Leftroom = 0;// Indentifies if the Right Room
int Home = 0; // if it is the second dead end
 
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12


 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void waitForButtonAndCountDown()  
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);

   for (int i = 0; i < 3; i++)
  {
    delay(500);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(500);
  buzzer.playNote(NOTE_G(4), 500, 15);  
  delay(500);
  
}


////////////////////////////////////////////////////
void Reverseifallblack() // check whether there is are black lines on front and turns 360 degree
{


sensors.read(sensor_values);

if (sensor_values[5]  > QTR_THRESHOLD && sensor_values[0] > QTR_THRESHOLD)
  {
    // if both sensor detects line, turn around
    
     motors.setSpeeds(-200, -187);
    delay(400);
     motors.setSpeeds(-200, 187);
    delay(920);
    Returningtobase = 1;
    motors.setSpeeds(0, 0);
    delay(20);
    Home + 1;
  }
}


//////////////////////////////////////////////////


 
void setup()
  {
        // uncomment if necessary to correct motor directions
         //motors.flipLeftMotor(true);
        //motors.flipRightMotor(true);
   
         pinMode(LED, HIGH);
         Serial.begin(9600);
         xbee.begin(9600);
         waitForButtonAndCountDown();
  }

void loop()
  {
      Serial.begin(9600); 
       if (button.isPressed())
        {
      // if button is pressed, stop and wait for another press to go again
        motors.setSpeeds(0, 0);
        button.waitForRelease();
      // waitForButtonAndCountDown();
        }


       Reverseifallblack();

      while (Home<2)
      {
   
        sensors.read(sensor_values);
        if (sensor_values[5]  > QTR_THRESHOLD && sensor_values[0] > QTR_THRESHOLD)
        {
           // if both sensor detects line, turn around
            if (Home<2)
            {
             motors.setSpeeds(-200, 187);
             delay(200);
            //  motors.setSpeeds(REVERSE_SPEED, -REVERSE_SPEED);
              delay(200);
            //  motors.setSpeeds(400, -400);
              delay(200);
      
             motors.setSpeeds(200, -187);
             }else{motors.setSpeeds(0, 0); }
             Home+1;
         } else 
          {

//////////////////////////////////////////////////////
  sensors.read(sensor_values);
  Reverseifallblack(); 
 motors.setSpeeds(200, 187); 
 delay(200);  
 motors.setSpeeds(0, 0); delay(50);  
 
Reverseifallblack(); 
motors.setSpeeds(-200, -187);   
delay(200); 
 motors.setSpeeds(0, 0); delay(50);
 
/////////////////////////////////////////////////////
 
  motors.setSpeeds(200, -187);   
  delay(170); 
    
  motors.setSpeeds(0, 0); delay(50);
  
  motors.setSpeeds(200, 186);
  delay(295);
  
  motors.setSpeeds(0, 0); delay(50);
 
 sensors.read(sensor_values);
 
if (sensor_values[5] > QTR_THRESHOLD) { Right_line = 1 ; }   
motors.setSpeeds(0, 0);
sensors.read(sensor_values);
if (sensor_values[5] > QTR_THRESHOLD) { Right_line = 1 ; } 
Serial.print(  sensor_values[5] );
  Serial.print("left");
  Serial.print(  Right_line );

 motors.setSpeeds(-200, -187);   
 delay(295); 
 motors.setSpeeds(0, 0); delay(50); 
 
Reverseifallblack();
motors.setSpeeds(-200, 200);
 delay(170); 
 
 motors.setSpeeds(0, 0);
  delay(10);
  /////////////////////////////////////////////////////////

  
 motors.setSpeeds(-200, 187); 
 delay(170);
  motors.setSpeeds(0, 0); delay(50);
 motors.setSpeeds(200, 187);
  delay(295);
  motors.setSpeeds(0, 0); delay(50);
  
  sensors.read(sensor_values);
  if (sensor_values[0] > QTR_THRESHOLD) { Left_line = 1 ; } 
 Serial.print( sensor_values[0]);   
 
   Serial.print("Left"); 
 Serial.print( Left_line);
  
 
 sensors.read(sensor_values);
  if (sensor_values[0] > QTR_THRESHOLD) { Left_line = 1 ; } 
  
 motors.setSpeeds(-200, -187);
 delay(295);
 motors.setSpeeds(0, 0); delay(50);
 
motors.setSpeeds(200, -187);
 delay(170);
  motors.setSpeeds(0, 0);delay(50);

/////////////////////////////////////////////////////////




if(Left_line == 1 && Right_line == 1)
{ 
  xbee.println( "Zumo is moving forward few steps");
  motors.setSpeeds(200, 185);
  delay(350);
  motors.setSpeeds(0, 0);delay(50);
  Reverseifallblack();
  Left_line = 0 ;
  Right_line = 0;

} else if (Left_line == 1 && Right_line == 0){
   xbee.println( "Zumo is Turning Right ");
   Rightroom = 1;
   Reverseifallblack();
   motors.setSpeeds(200, 185);
   Reverseifallblack();
  delay(350);
  motors.setSpeeds(200, -185); 

  if (Secondrightturn == 0 ) {
delay(440);
Secondrightturn = 1;
  }else{
     if (Returningtobase == 0){
    delay(460);
     }else{delay(470);}
  }
  motors.setSpeeds(0, 0);
delay(10);
Left_line = 0 ;
Right_line = 0;
Reverseifallblack();
 motors.setSpeeds(200, 185);

 if (Returningtobase == 0){
 
 delay(3000);

}else{
  
  
  delay(350); }




  }else if (Left_line == 0 && Right_line == 1){
    xbee.println( "Zumo is Turning Left ");
Leftroom = 1;
Reverseifallblack();
  motors.setSpeeds(200, 185);
  Reverseifallblack();
  delay(300);
  motors.setSpeeds(-200, 185); 
delay(350);
  motors.setSpeeds(200, 200);
delay(200);
Reverseifallblack();
Left_line = 0 ;
Right_line = 0;
  }



  else if (Left_line == 0 && Right_line == 0){
xbee.println( "Zumo has entered into a room and scanning for a object  ");
  motors.setSpeeds(200, 185);
  delay(300);
  motors.setSpeeds(-150, 140); 

 
//////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Checking if there is a physical object using ultrasonic sensor

for (int x= 0; x < 30; x++) {

delay(100);      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if( sonar.ping_cm() > 2 && sonar.ping_cm() < 15){
  Serial.println("found");
  xbee.println( "found object");
  }
}



  
  

  
////////////////////////////////////
delay(1400);


  motors.setSpeeds(0, 0);
delay(50);
motors.setSpeeds(200, 185);
delay(600);


if (Rightroom ==1) {
motors.setSpeeds(200, -185);}else{ motors.setSpeeds(-200, 185); }


delay(460);
motors.setSpeeds(0, 0);
delay(50);
Reverseifallblack();
Left_line = 0 ;
Right_line = 0;
Rightroom = 0;
Leftroom = 0;
motors.setSpeeds(200, 187);
delay(300);
motors.setSpeeds(0, 0);
delay(50);

  } /* else if (Left_line == 1 && Right_line == 1){

   /
     motors.setSpeeds(-200, 185);
    delay(200);
  //  motors.setSpeeds(REVERSE_SPEED, -REVERSE_SPEED);
    delay(200);
 //  motors.setSpeeds(400, -400);
    delay(200);
    motors.setSpeeds(200, -185);

  }*/
Left_line = 0 ;
Right_line = 0;

}}
 // motors.setSpeeds(0, 0);  
  
}
