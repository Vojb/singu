#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <Servo.h>
#include <IRremoteInt.h>
#include <SoftwareSerial.h>

#define WHEEL_LEFT_MOTOR 9
#define WHEEL_LEFT_BACKWARD 8

#define WHEEL_RIGHT_MOTOR 10
#define WHEEL_RIGHT_BACKWARD 11
#define ULTRA_TRIG_PIN 14
#define ULTRA_ECHO_PIN  15

#define SOUND_PIN  2
#define SERVO_PIN  12
#define DISTANCE_MIN 50


int RECV_PIN = 13;

//This lets you run the loop a single time for testing
boolean run = true;

Servo ultra_sight_servo;
SoftwareSerial mySerial(10, 11);
IRrecv irrecv(RECV_PIN);
decode_results results;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  right_side_stop();
  left_side_stop();


  ultra_sight_servo.attach(SERVO_PIN);
  ultra_sight_servo.write(180);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(SOUND_PIN,OUTPUT);
  

  // set the data rate for the SoftwareSerial port

  pinMode(LED_BUILTIN, OUTPUT);


}
void right_side_stop() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
void left_side_stop() {
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}
void right_side_forwards() {
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

}
void right_side_backwards() {
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}
void left_side_backwards() {
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}
void left_side_forwards() {
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);

}
float mallet_distance()
{
  pinMode(ULTRA_TRIG_PIN, OUTPUT);
  digitalWrite(ULTRA_TRIG_PIN, LOW);
  delayMicroseconds(5);

  digitalWrite(ULTRA_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG_PIN, LOW);

  pinMode(ULTRA_ECHO_PIN, INPUT);
  long duration = pulseIn(ULTRA_ECHO_PIN, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  float distance = duration / 58.2;
  return (duration / 2) / 29.1;
}
float mallet_try(int trig, int echo)
{
  pinMode(trig, OUTPUT);

  digitalWrite(trig, LOW);
  delayMicroseconds(5);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  long duration = pulseIn(echo, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  float distance = duration / 58.2;
  return (duration / 2) / 29.1;
}

// the loop function runs over and over again forever
void loop() {
  Serial.print(":");
  Serial.print(mallet_distance());
  Serial.println("<..>");
  delay(1000);
  Serial.print(":");
  Serial.print("to close");
  Serial.println("<..>");

 Serial.println("sound");
 Serial.println(digitalRead(SOUND_PIN));
    ultra_sight_servo.write(mallet_distance());
 
   
}
