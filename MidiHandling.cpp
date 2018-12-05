#include "MidiHandling.h"


MidiHandling::MidiHandling(){
}

int MidiHandling::calculateNote(int string, int fret){	// Converts a string and a fret to a midi note
	return 28 + fret + (string * 5);
}

void MidiHandling::on(int string, int fret){

	off(string);
	midiNoteOn(CHANNEL, calculateNote(string, fret), 127);		// Turns of the last instance and on the new one
	activeMidiNote[string] = fret;								// Stors the new instance
}

void MidiHandling::off(int string){

	if(activeMidiNote[string] >= 0){
		midiNoteOff(CHANNEL, calculateNote(string, activeMidiNote[string]), 0);			// Checks if the last instance has been initialized and turns it of if it has
	}
	activeMidiNote[string] = -1;

}


void MidiHandling::midiNoteOn(byte channel, byte pitch, byte velocity) {
	if(pitch != 255){	
	  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};	// Sends a note on message
	  MidiUSB.sendMIDI(noteOn);

	  if(DEBUG){
	  	Serial.println(String(pitch) + " ON");
	  }
	}
}

void MidiHandling::midiNoteOff(byte channel, byte pitch, byte velocity) {
  if(pitch != 255){
	midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};	// Sends a note off message
	MidiUSB.sendMIDI(noteOff);

	if(DEBUG){
		Serial.println(String(pitch) + " OFF");
	}
  }
}

String MidiHandling::getActiveMidiNoteString(){		// Returns the active midinotes as a string
	String output = "[";

    for(int i = 0; i < NROFSTRINGS; i++ ){
      output += String(activeMidiNote[i]);

      if(i < NROFSTRINGS - 1){
        output += String(", ");
      }
    }
    return output + "]";
}
