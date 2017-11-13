#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>


#define STATE_STARTING        0
#define STATE_MOVING_FORWARD  1
#define STATE_MOVING_SPINNING 2
#define STATE_MOVING_BACKWARD 3
#define STATE_MOVING_STILL    4
#define STATE_SEARCHING_PATH  5

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT  1

#define DISTANCE_MIN 100 

#define WHEEL_LEFT_MOTOR 9
#define WHEEL_LEFT_BACKWARD 8

#define WHEEL_RIGHT_MOTOR 10
#define WHEEL_RIGHT_BACKWARD 11
#define ULTRA_TRIG_PIN 14
#define ULTRA_ECHO_PIN  15

#define SERVO_PIN  12

Servo ultra_sight_servo;

typedef uint8_t State;
typedef uint8_t Direction;

typedef struct SpinData
{
  int angle;
  Direction direction;
} SpinData;

typedef struct Robot
{
  State state;
  SpinData spin_data;
} Robot;


uint8_t _state = STATE_STARTING;
SpinData _spin_data;

int distance_current();
void state_set();

void init_spin_data()
{
  _spin_data.direction = DIRECTION_RIGHT;
  _spin_data.angle = 0;
}



void state_set(int state)
{
  _state = state;
}




void handle_state_starting()
{
}

bool motors_stopped()
{
  return true;
}

void right_side_stop() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
void left_side_stop() {
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}

void motors_right_forward()
{
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
}
void motors_left_forward()
{
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
}
void motors_right_backward()
{
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}
void motors_left_backward()
{
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}



void motors_backward()
{
  motors_left_backward();
  motors_right_backward();
}

void motors_spinn_right()
{
}

void motors_spinn_left()
{
}

void motors_left_stop()
{
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}

void motors_right_stop()
{
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void motors_stop()
{
  motors_left_stop();
  motors_right_stop();
  motors_stopped();
}
void motors_forward()
{
  motors_stop();
  motors_left_forward();
  motors_right_forward();
}
float get_distance()
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

void distance_find_left_max(int *angle, float *distance)
{
}

void distance_find_right_max(int *angle, float *distance)
{
}

void set_state_moving_spinning(int angle, Direction direction)
{
  _spin_data.angle = angle;
  _spin_data.direction = direction;
  state_set(STATE_MOVING_SPINNING);
}

void handle_state_searching_path()
{
  int angle_left = -1;
  int angle_right = -1;

  float distance_left = -1;
  float distance_right = -1;

  distance_find_left_max(&angle_left, &distance_left);
  distance_find_right_max(&angle_right, &distance_right);

  float distance_target = distance_right;
  int angle_target = angle_right;
  Direction direction = DIRECTION_RIGHT;

  if (distance_left > distance_target)
  {
    distance_target = distance_left;
    angle_target = angle_target;
    direction = DIRECTION_LEFT;
  }

  if (distance_target < DISTANCE_MIN)
  {
    state_set(STATE_MOVING_BACKWARD);
    return;
  }

  set_state_moving_spinning(angle_target, direction);
}

void handle_state_moving_still()
{
  motors_stop();
  //state_set(STATE_SEARCHING_PATH);
  motors_right_backward();

  delay(2000);
  state_set(STATE_MOVING_FORWARD); 
}
int distance_current()
{
  return 0;
}

bool distance_too_close()
{
  return get_distance() < DISTANCE_MIN;
}
void handle_state_moving_forward()
{
  motors_forward();
  if (distance_too_close())
  {
    state_set(STATE_MOVING_STILL);
    return;
  }

  if (motors_stopped())
  {
    motors_forward();
  }
}

void handle_state()
{
  switch(_state)
  {
      case STATE_MOVING_FORWARD: 
      Serial.write("in state");
      handle_state_moving_forward();
      break;
      case STATE_MOVING_STILL:
       handle_state_moving_still();
       break;
  }
}
int distance;
void setup()
{
    Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  distance = get_distance();
  ultra_sight_servo.attach(SERVO_PIN);
  pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);
  pinMode(WHEEL_LEFT_MOTOR, OUTPUT);
  pinMode(WHEEL_RIGHT_MOTOR, OUTPUT);
  pinMode(WHEEL_RIGHT_BACKWARD, OUTPUT);
  motors_stop();
  delay(5000);

  motors_forward();

}
void loop()
{
  Serial.println("distance:");       
  Serial.println(get_distance());
  if(get_distance()<DISTANCE_MIN){

  Serial.println("börjar backa");
   motors_right_backward();
   motors_left_forward();
   delay(100);
   motors_forward();
  }

 

   


 
}
