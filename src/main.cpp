#define STATE_STARTING
#define STATE_MOVING_FORWARD
#define STATE_MOVING_SPINNING
#define STATE_MOVING_BACKWARD
#define STATE_MOVING_STILL
#define STATE_SEARCHING_PATH

#define DISTANCE_MIN 30 

uint8_t _state = STATE_STARTING

void setup()
{

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


void motors_left_stop()
{
}

void motors_right_stop()
{
}

void motors_stop()
{
}

void handle_state_moving_still()
{
  motors_stop();
}

void handle_state_moving_forward()
{
  if (distance_too_close())
  {
    state_set(STATE_MOVING_STILL);
    return;
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
