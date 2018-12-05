#include "Strings.h"

Strings::Strings(){
  for(int i = 0; i < NROFSTRINGS; i++ ){    // Inits the string reading
    pinMode(OUTPUTPIN[i], OUTPUT);
    digitalWrite(OUTPUTPIN[i], HIGH);
  }

  for(int i = 0; i < NROFPINS; i++ ){
    pinMode(INPUTPIN[i], INPUT_PULLUP);
  }
}

int Strings::calculateInput(uint32_t values){
  for(int i = NROFPINS; i > 0; i-- ) {      // Extracts the position of the first 1 in the bit stream, to get the highest band that is currently active
    if(values & 0x1 == 1){
      return i;
    }
    values = values >> 1;
  }

  return 0;
}

String Strings::uint32_tToString(uint32_t inputVal) {  // Converts 20 bits to a string
  String output = "";
  
  for(int j = 0; j < NROFPINS; j++ ) {
    output += String(inputVal & 0x1);
    inputVal = inputVal >> 1;
  }
  return output;
}

uint32_t Strings::readInput(){     // Appends the input of every fret and appends it to a bit array, with the highest band on the least significant position
  uint32_t output = 0;

  for(int i = NROFPINS - 1; i >= 0; i-- ){
    output = (output << 1) | !bitRead(*INPUTBYTE[i], INPUTBIT[i]);
  }

  // if(DEBUG) Serial.println(uint32_tToString(output));
  
  return output;
}

void Strings::read(){

  for(int i = NROFSTRINGS - 1; i >= 0; i-- ){   // Goes through every string, activates it and reads it
    digitalWrite(OUTPUTPIN[i], LOW);
    delay(1);

    tempInput = calculateInput(readInput());

    if(tempInput != lastFret[i]){
      fretChanged[i] = true;
      lastFret[i] = tempInput;
      lastString = i;
    }

    digitalWrite(OUTPUTPIN[i], HIGH);
  }

}

bool Strings::getFretChanged(int instance) {
  if(instance < NROFSTRINGS && instance >= 0) {
    return fretChanged[instance];
  }
  else {
    if(DEBUG) {
      Serial.println("Something tried to accsess fretChanged[" + String(instance) + "]");
    }
    return false;
  }
}

int Strings::getLastFret(int instance) {
  if(instance < NROFSTRINGS && instance >= 0) {
    return lastFret[instance];
  }
  else {
    if(DEBUG) {
      Serial.println("Something tried to accsess lastFret[" + String(instance) + "]");
    }
    return -1;
  }
}

int Strings::getLastString(){
  return lastString;
}

void Strings::clear(){
  for(int i = 0; i < NROFSTRINGS; i++ ){
    fretChanged[i] = false;
  }
}