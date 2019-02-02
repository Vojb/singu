#include <Arduino.h>
#include <stdint.h>

#define BAUD_RATE 9600

#define CMD_FORWARD 'f'
#define CMD_BACKWARD 'b'
#define CMD_SPIN_RIGHT 'r'
#define CMD_SPIN_LEFT 'l'
#define CMD_STOP 's'

#define PIN_CONNECTED 2

#define WHEEL_LEFT_BACKWARD 8
#define WHEEL_LEFT_MOTOR_ON 9

#define WHEEL_RIGHT_MOTOR_ON 10
#define WHEEL_RIGHT_FORWARD 11

char _cmd = 0;
char _last_cmd = 0;

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
  digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
}

void setup()
{
  motors_stop();

  pinMode(WHEEL_RIGHT_MOTOR_ON, OUTPUT);
  pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);

  pinMode(WHEEL_LEFT_MOTOR_ON, OUTPUT);
  pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);

  pinMode(PIN_CONNECTED, INPUT);

  Serial.begin(BAUD_RATE);
}

void loop()
{
  if (digitalRead(PIN_CONNECTED) == LOW)
  {
    if (_last_cmd == CMD_STOP)
    {
      return;
    }

    _last_cmd = CMD_STOP;
    motors_stop();
    return;
  }

  if (Serial.available() <= 0)
  {
    return;
  }

  _cmd = Serial.read();
  if (_last_cmd == _cmd)
  {
    return;
  }

  _last_cmd = _cmd;
  switch (_cmd)
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
  case CMD_STOP:
    motors_stop();
  }
}
