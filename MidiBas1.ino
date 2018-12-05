#import "Consts.h"
#import "Strings.h"
#import "TouchHandling.h"
#import "MidiHandling.h"

TouchHandling* touchHandler;  // An object handling the touchscreen and rendering
MidiHandling* midiHandler;    // An object handling all midi comunication and stores the notes that is currently played
Strings* stringHandler;       // An object handling the reading of the strings and parsing of the current position

uint32_t lastTime;

bool temp;

void parseInput();
void onActive();
void onPassive();

void setup(){

  if(DEBUG){
    Serial.begin(9600);
    Serial.println("Begin!");
  }

  touchHandler = new TouchHandling();

  stringHandler = new Strings(); 

  midiHandler = new MidiHandling();

  delay(1000);

}


void loop(){

  lastTime = millis();

  parseInput();   // Reads the input and sends apropiate midi data

  // Serial.println(midiHandler->getActiveMidiNoteString());
  
  touchHandler->render(); // Render the screen, and clears flags
  touchHandler->clear();
  stringHandler->clear();

  //if(DEBUG) Serial.println("Timing: " + String(millis() - lastTime));
    
}

void parseInput() {

  touchHandler->read();
  stringHandler->read();

  
  if(touchHandler->getTouchActivitionChanged()){    // Check if a touchevent has been initialized or if the position has been changed

    onActive();
  
  }
  else {

    onPassive();

  }

  if(touchHandler->getTouchPositionChanged()){
    // TODO: Add stuff
  }

  

}

void onActive(){

  //Serial.println("TouchActivation: " + String(touchHandler->getTouchActivation()));

  if(touchHandler->getTouchActivation()) {    // If the activation has changed, and there is a touch event

    temp = false;

      for(int i = 0; i < NROFSTRINGS; i++ ){

        if(stringHandler->getLastFret(i) > 0){    // Goes through every string and checks if any of them are active (If there is any fret that is pressed upon)
          temp = true;
          midiHandler->on(i, stringHandler->getLastFret(i));  // Sends the apropiat midi data if so
        }

      }

      if(!temp){                                                                                                        // If no string has been activated, but there is a touch event
        midiHandler->on(stringHandler->getLastString(), stringHandler->getLastFret(stringHandler->getLastString()));    // it sends the last activated strings zero-value
      }

  }
  else{                                                 // If the touch has changed and the touch event has ended, it turns all the midi notes off

    for(int i = 0; i < NROFSTRINGS; i ++ ){
      midiHandler->off(i);
    }

  }

}

void onPassive() {    // If the touchevent has stayed the same since the last cycle

  if(touchHandler->getTouchActivation()){             // Check is there is an active event

    for(int i = 0; i < NROFSTRINGS; i++ ){

      if(stringHandler->getFretChanged(i)){           // Goes through every string and checks if any fret has changed. Sends the midi data if so

        if(stringHandler->getLastFret(i) > 0){
          midiHandler->on(i, stringHandler->getLastFret(i));
        }
        else{
          midiHandler->off(i);
        }
      }

    }
  }

}