#include "button.h"
#include "main.h"

#define DEBOUNCE_MS 50

static bool was_pressed = false;
static bool stable_pressed = false;
static bool press_event = false;
static uint32_t changed_at = 0;

void button_poll(void)
{
  bool now_pressed = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_RESET;

  if (now_pressed != was_pressed) {
    was_pressed = now_pressed;
    changed_at = HAL_GetTick();
  } else if (was_pressed != stable_pressed && HAL_GetTick() - changed_at >= DEBOUNCE_MS) {
    stable_pressed = was_pressed;
    if (stable_pressed) {
      press_event = true;
    }
  }
}

bool button_held(void)
{
  return stable_pressed;
}

bool button_clicked(void)
{
  if (press_event) {
    press_event = false;
    return true;
  }
  return false;
}
