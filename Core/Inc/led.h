#ifndef LED_H
#define LED_H

#include <stdbool.h>

typedef enum {
  LED_GREEN,
  LED_YELLOW,
  LED_RED
} led_t;

void led_set(led_t led, bool on);
void led_all_off(void);

#endif
