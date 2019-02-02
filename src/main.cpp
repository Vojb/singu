#include <Arduino.h>
#include <stdint.h>

#define BAUD_RATE 9600

#define CMD_FORWARD 'f'
#define CMD_BACKWARD 'b'
#define CMD_SPIN_RIGHT 'r'
#define CMD_SPIN_LEFT 'l'

#define WHEEL_LEFT_MOTOR_ON 9
#define WHEEL_LEFT_BACKWARD 8

#define WHEEL_RIGHT_MOTOR_ON 10
#define WHEEL_RIGHT_FORWARD 11

uint8_t _available = 0;
char _cmd = 0;
char _last_cmd = 0;
unsigned long _last_cmd_at = 0;
bool _moving = false;

void motors_spin_right()
{
  _moving = true;
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, LOW);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
}

void motors_spin_left()
{
  _moving = true;
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
}

void motors_forward()
{
  _moving = true;
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
}

void motors_backward()
{
  _moving = true;
  digitalWrite(WHEEL_RIGHT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_RIGHT_FORWARD, LOW);

  digitalWrite(WHEEL_LEFT_MOTOR_ON, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
}

void motors_stop()
{
  _moving = false;
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

  _available = Serial.available();
  while (_available > 0)
  {
    /*
    for (uint8_t i = 0; i < _available; i++)
    {
      _cmd = Serial.read();
    }
    */

    _cmd = Serial.read();
    _last_cmd_at = millis();
    if (_last_cmd == _cmd) {
      continue;
    }

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
    }
    _available = Serial.available();
  }

  if (_moving && (millis() - _last_cmd_at) > 100)
  {
    motors_stop();
  }
}
