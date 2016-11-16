#ifdef WIN32
extern int analogRead(int);
extern int analogWrite(int,int);
#define A0 0
#include "tinyrace.ino"
#endif
