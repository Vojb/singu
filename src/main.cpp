#include <Arduino.h>
#include <stdint.h>

#define BAUD_RATE 9600

#define STATE_STARTING 0
#define STATE_MOVING_FORWARD 1
#define STATE_MOVING_SPINNING 2
#define STATE_MOVING_BACKWARD 3
#define STATE_MOVING_STILL 4
#define STATE_SEARCHING_PATH 5

#define CMD_FORWARD 'f'
#define CMD_BACKWARD 'b'
#define CMD_SPIN_RIGHT 'r'
#define CMD_SPIN_LEFT 'l'

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1

#define WHEEL_LEFT_MOTOR_ON 9
#define WHEEL_LEFT_BACKWARD 8

#define WHEEL_RIGHT_MOTOR_ON 10
#define WHEEL_RIGHT_FORWARD 11

unsigned long _last_cmd = 0;

void motors_spin_right()
{
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, LOW);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
}

void motors_spin_left()
{
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
}

void motors_forward()
{
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
}

void motors_backward()
{
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, LOW);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
}

void motors_stop()
{
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, LOW);
  digitalWrite(WHEEL_RIGHT_FORWARD, LOW);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, LOW);
  digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
}

void setup()
{
  motors_stop();

  pinMode(WHEEL_RIGHT_MOTOR_ON, OUTPUT);
  pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);

  pinMode(WHEEL_LEFT_MOTOR_ON, OUTPUT);
  pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);

  Serial.begin(BAUD_RATE);
}

void loop()
{
  char cmd = NULL;
  while (Serial.available() > 0)
  {
    cmd = Serial.read();
    switch (cmd)
    {
    case CMD_FORWARD:
      motors_forward();
      break;
    case CMD_BACKWARD:
      motors_backward();
      break;
    case CMD_SPIN_RIGHT:
      motors_spin_right();
      break;
    case CMD_SPIN_LEFT:
      motors_spin_left();
      break;
    }
  }
  if (cmd != NULL)
  {
    delay(75);
  }

  motors_stop();
}
