
// common functions
void DelayMs (int ms);
void hardwareInit();

#ifdef BACKENDPC
#include <SDL/SDL.h>
#define USW0        SDLK_w
#define USW1        SDLK_a
#define USW2        SDLK_d
#define USW3        SDLK_s
#else
#include "target.h"
#endif

