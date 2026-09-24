#include "garland.h"
#include "led.h"
#include "main.h"

#define GREEN  0b001
#define YELLOW 0b010
#define RED    0b100

#define MODES 4

static const uint8_t frames[MODES][2] = {
  { GREEN, YELLOW },
  { GREEN, RED },
  { GREEN | YELLOW, 0 },
  { GREEN | RED, 0 },
};
static const uint32_t periods[MODES] = { 500, 300, 150, 70 };

static uint8_t positions[MODES];
static uint8_t mode = 0;
static uint32_t last_step = 0;

static void show(void)
{
  uint8_t frame = frames[mode][positions[mode]];

  led_set(LED_GREEN, frame & GREEN);

  if (frame & YELLOW) {
    led_set(LED_YELLOW, true);
  } else if (frame & RED) {
    led_set(LED_RED, true);
  } else {
    led_set(LED_YELLOW, false);
    led_set(LED_RED, false);
  }

  last_step = HAL_GetTick();
}

void garland_init(void)
{
  show();
}

void garland_next(void)
{
  mode = (mode + 1) % MODES;
  show();
}

void garland_poll(void)
{
  if (HAL_GetTick() - last_step >= periods[mode]) {
    positions[mode] = (positions[mode] + 1) % 2;
    show();
  }
}
