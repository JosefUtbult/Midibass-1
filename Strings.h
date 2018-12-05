#ifndef STRINGS_H
#define STRINGS_H
#include "Consts.h"

class Strings
{
public:
	Strings();
	void read();
	String uint32_tToString(uint32_t inputVal);
	bool getFretChanged(int instance);
	int getLastFret(int instance);
	int getLastString();
	void clear();

private:

	int lastFret[NROFSTRINGS] = {-1, -1, -1, -1};
	bool fretChanged[NROFSTRINGS] = {false, false, false, false};
	int tempInput;
	int lastString = 0;

	uint32_t readInput();	
	int calculateInput(uint32_t values);

};

#endif