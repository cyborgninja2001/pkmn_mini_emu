#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// get the 'n' bit of 'a'
#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)

// set the 'n' bit of 'a' with value 'v'
#define BIT_SET(a, n, v) { if (v) a |= (1 << n); else a &= ~(1 << n);}

#endif