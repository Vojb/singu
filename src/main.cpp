#define STATE_STARTING
#define STATE_MOVING_FORWARD
#define STATE_MOVING_SPINNING
#define STATE_MOVING_BACKWARD
#define STATE_MOVING_STILL
#define STATE_SEARCHING_PATH

#define DIRECTION_RIGHT = 0
#define DIRECTION_LEFT = 1

#define DISTANCE_MIN 30 

typedef uint8_t Direction;

typedef struct 
{
  int angle;
} SpinData;

uint8_t _state = STATE_STARTING
SpinData _spin_data;

void init_spin_data()
{
  _spin_data.direction = DIRECTION_RIGHT;
  _spin_data.angle = 0;
}

void setup()
{
  init_spin_data();
}

bool distance_too_close()
{
  return distance_current()
}

float distance_current()
{
  return 0;
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
  _sping_data.direction = direction
  set_state(STATE_MOVING_SPINNING);
}

void handle_state_searching_path()
{
  int angle_left = -1;
  int angle_right = -1;
  int angle_target = -1;

  float distance_left = -1;
  float distance_right -1;
  float distance_target = -1;


  distance_find_left_max(*angle_left, *distance_left);
  distance_find_right_max(*angle_right, *distance_right);


  float distance_target = distance_right;
  int angle_target = angle_right;
  Direction direction = DIRECTION_RIGHT;

  if (distance_left > target_distance)
  {
    distance_target = distance_left;
    angle_target = angle_target;
    direction = DIRECTION_LEFT;
  }

  if (distance_target < DISTANCE_MIN)
  {
    set_state(STATE_MOVING_BACKWARD);
    return;
  }

  switch(direction)
  {
    case DIRECTION_RIGHT:
      set_state_moving_spinning((angle_target - 90), direction);
      break;
    case DIRECITON_LEFT:
      set_state_moving_spinning(direction);
      break;
  }

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
