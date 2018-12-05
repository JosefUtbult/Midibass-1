#ifndef CONSTS_H
#define CONSTS_H

#include <Arduino.h>

#define CHANNEL 1
#define DEBUG true

#define SCREENWIDTH 1023
#define SCREENHEIGHT 599
#define MIDIACCUR 127

#define RED 250
#define GREEN 200
#define BLUE 176

#define BLACKOUT 1000

static const int NROFPINS = 20;
static const int NROFSTRINGS = 4;

static const int OUTPUTPIN[NROFSTRINGS] = {
  42, 43, 44, 45
};
static const int OUTPUTBIT[NROFSTRINGS] = {
  19, 20, 19, 18
};

static const RoReg* OUTPUTBYTE[NROFSTRINGS] = {
  &REG_PIOA_PDSR, &REG_PIOA_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR
};

static const int INPUTBIT[NROFPINS] = {
  26, 14, 15, 0, 1, 
  2, 3, 6, 9, 7, 
  10, 1, 2, 3, 4,
  5, 6, 7, 8, 9

};

static const RoReg* INPUTBYTE[NROFPINS] = {
  &REG_PIOB_PDSR, &REG_PIOA_PDSR, &REG_PIOA_PDSR, &REG_PIOD_PDSR, &REG_PIOD_PDSR,
  &REG_PIOD_PDSR, &REG_PIOD_PDSR, &REG_PIOD_PDSR, &REG_PIOD_PDSR, &REG_PIOA_PDSR,
  &REG_PIOD_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR,
  &REG_PIOC_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR, &REG_PIOC_PDSR
};

static const int INPUTPIN[NROFPINS] = {
  22, 23, 24, 25, 26, 
  27, 28, 29, 30, 31,
  32, 33, 34, 35, 36,
  37, 38, 39, 40, 41
};

#endif