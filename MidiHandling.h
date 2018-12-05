#ifndef MIDIHANDLING_H
#define MIDIHANDLING_H

#include <MIDIUSB.h>
#include "Consts.h"
#include "TouchHandling.h"

class MidiHandling
{
public:

	MidiHandling();
	void on(int string, int fret);
	void off(int string);

	String getActiveMidiNoteString();

private:

	int calculateNote(int string, int fret);
	void midiNoteOn(byte channel, byte pitch, byte velocity);
	void midiNoteOff(byte channel, byte pitch, byte velocity);

	int activeMidiNote[NROFSTRINGS] = {-1, -1, -1, -1};
	int currentNote;
	int lastString = 0;
	bool tempBool;

};

#endif
