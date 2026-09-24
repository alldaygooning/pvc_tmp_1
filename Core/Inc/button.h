#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

void button_poll(void);
bool button_held(void);
bool button_clicked(void);

#endif
