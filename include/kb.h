/**
* Chipset 8042
* PS/2 Controller (often called a "Keyboard controller")
*/

#ifndef KB_H
#define KB_H
#include "screen.h"

#define PS2_STATUS_REGISTER 0x64
#define PS2_DATA_PORT 0x60

string readStr();

#endif
