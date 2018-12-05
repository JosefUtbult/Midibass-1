#ifndef TOUCHHANDLING_H
#define TOUCHHANDLING_H

#include <SPI.h>
#include <Wire.h>
#include <FT5206.h>

#include "RA8876.h"

#include "Consts.h";

#define RA8876_CS 10
#define RA8876_RESET 9
#define RA8876_BACKLIGHT 8  
#define CTP_INT 7 // touch data ready for read from FT5206 touch controller

class TouchHandling
{
public:
	TouchHandling();

	void read();
	void render();
	void clear();

	int getTouchStatus();
	int getTouchPositionX();
	int getTouchPositionY();
	bool getTouchActivation();
	bool getTouchActivitionChanged();
	bool getTouchPositionChanged();


private:

	bool temp = false;
	int tempTouchRead;
	int oldTouchStatus;
	int touchStatus;
	bool touchActivitionChanged = false;
	bool touchActivation;
	bool touchPositionChanged = false;

	const double deltaWidth = double(MIDIACCUR) / double(SCREENWIDTH);
	const double deltaHeight = double(MIDIACCUR) / double(SCREENHEIGHT);

	uint8_t registers[FT5206_REGISTERS];
	uint16_t cordinateBuffer[5][2];
	uint16_t new_coordinates[2] = {0, 0}; 
	uint16_t old_coordinates[2] = {0, 0}; 

	uint8_t current_touches = 0;
	uint8_t old_touches = 0;

	uint8_t i;
	uint16_t x,y;

	uint32_t currentTime;
	uint32_t lastTouch;
	bool cleared;

	RA8876 screen = RA8876(RA8876_CS, RA8876_RESET);
	FT5206 touch = FT5206(CTP_INT);

	void drawCircle(int posX, int posY);
	int readCordinates();

		
};

#endif
