#include <stdint.h>
#include <Arduino.h>

#define STATE_STARTING        0
#define STATE_MOVING_FORWARD  1
#define STATE_MOVING_SPINNING 2
#define STATE_MOVING_BACKWARD 3
#define STATE_MOVING_STILL    4
#define STATE_SEARCHING_PATH  5

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT  1

#define DISTANCE_MIN 30 

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

void setup()
{
  init_spin_data();
}

void state_set(int state)
{
  _state = state;
}

int distance_current()
{
  return 0;
}

bool distance_too_close()
{
  return distance_current() < DISTANCE_MIN;
}


void handle_state_starting()
{
}

bool motors_stopped()
{
  return true;
}

void motors_forward()
{
}

void motors_backward()
{
}

void motors_spinn_right()
{
}

void motors_spinn_left()
{
}

void motors_left_stop()
{
}

void motors_right_stop()
{
}

void motors_stop()
{
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
  state_set(STATE_SEARCHING_PATH); 
}

void handle_state_moving_forward()
{
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

  }
}

void loop()
{
  handle_state();
}
