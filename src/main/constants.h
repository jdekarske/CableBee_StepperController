#ifndef CONSTANTS_H
#define CONSTANTS_H

// The stepper breakout board has x,y,z axes because it is for a CNC machine. I'm looking at the silkscreen
#define XSTEP 16
#define YSTEP 18
#define ZSTEP 20

#define XDIR 17
#define YDIR 19
#define ZDIR 21

#define STEP_OUTPUTS ((1ULL<<XSTEP) | (1ULL<<YSTEP) | (1ULL<<ZSTEP) | (1ULL<<XDIR) | (1ULL<<YDIR) | (1ULL<<ZDIR))

#endif