#include "TouchHandling.h"
// Initializes the touchscreen
TouchHandling::TouchHandling(){
	if (!DEBUG)
		Serial.begin(9800); // This is neccicary (For some screen reason)
	pinMode(RA8876_BACKLIGHT, OUTPUT); // Iitializes the screen, the touch and clears the screen
	digitalWrite(RA8876_BACKLIGHT, HIGH);
	if (!screen.init()){
		if (DEBUG){
			Serial.println("Could not initialize Screen");
			lastTouch = millis();
			return;
		}
	}
	touch.begin();
	screen.clearScreen(0);
	if (DEBUG){
		Serial.println("Initialized Screen");
	}
	lastTouch = millis();
}

void TouchHandling::read(){
	touchStatus = readCordinates();
	if ((oldTouchStatus == 0 && touchStatus > 0) || (oldTouchStatus > 0 && touchStatus == 0)){
		touchActivitionChanged = true;
		touchActivation = touchStatus > 0;
	}
	if (touchStatus == 1){
		touchPositionChanged = true;
	}
	if (DEBUG){
		/*
		Serial.println(	"Touchstatus: " + String(touchStatus) +
		" x: " + String(new_coordinates[0]) +
		" y: " + String(new_coordinates[1]) +
		" touchActivation: " + String(touchActivation) +
		" touchActivitionChanged: " + String(touchActivitionChanged) +
		" touchPositionChanged: " + String(touchPositionChanged)
		);
		*/
	}
	oldTouchStatus = touchStatus;
}

void TouchHandling::render(){
	if (touchStatus == 1){
		drawCircle(int(float(new_coordinates[0]) / deltaWidth), int(float(new_coordinates[1]) / deltaHeight)); // Draws a circle if the touch possition just changed
		lastTouch = millis();
	}
	else
		if (touchStatus == 0){
			// Waits for the blackout time to clear the screen after there is no touch longer
			currentTime = millis();
			if (!cleared && BLACKOUT < currentTime - lastTouch)
			{
				screen.clearScreen(0);
				cleared = true;
			}
		}
	else
		if (touchStatus == 2){
			lastTouch = millis(); // Does nothing as the touch is still active at the same position
		}
	else{
		if (DEBUG){
			Serial.println("This should not be happening.");
		}
	}
}

void TouchHandling::drawCircle(int posX, int posY){
	cleared = false;
	screen.clearScreen(0); // Draws circles on top of each other with lighter and lighter colors, to make a light effect
	for (int i = 1; i < 11; i++){
		screen.fillCircle(posX, posY, 20 + 10 * (11 - i), RGB565(max(RED - 10 * (20 - i), 0), max(GREEN - 10 * (20 - i), 0), max(BLUE - 10 * (20 - i), 0)));
	}
	screen.fillCircle(posX, posY, 20, RGB565(max(RED - 10, 0), max(GREEN - 12, 0), max(BLUE - 12, 0)));
}

int TouchHandling::readCordinates(){
	if (touch.touched()){
		touch.getTSregisters(registers);
		current_touches = touch.getTScoordinates(cordinateBuffer, registers);
	}
	if (current_touches > 0){
		new_coordinates[0] = uint16_t(double(SCREENWIDTH - cordinateBuffer[current_touches - 1][0]) * deltaWidth);
		new_coordinates[1] = uint16_t(double(SCREENHEIGHT - cordinateBuffer[current_touches - 1][1]) * deltaHeight);
		if (new_coordinates[0] != old_coordinates[0] || new_coordinates[1] != old_coordinates[1]){
			old_coordinates[0] = new_coordinates[0];
			old_coordinates[1] = new_coordinates[1]; // Returns 1 if the current touch position has changed or a new one has activated
			return 1;
		}
		return 2; // Returns 2 if there is an active touch event that hasnt changed position since last time
	}
	else{
		return 0; // Returns 0 if there is no touch event at the moment
	}
}

void TouchHandling::clear(){
	touchActivitionChanged = false;
	touchPositionChanged = false;
}

int TouchHandling::getTouchStatus(){
	return touchStatus;
}

int TouchHandling::getTouchPositionX(){
	return new_coordinates[0];
}

int TouchHandling::getTouchPositionY(){
	return new_coordinates[1];
}

bool TouchHandling::getTouchPositionChanged(){
	return touchPositionChanged;
}

bool TouchHandling::getTouchActivitionChanged(){
	return touchActivitionChanged;
}

bool TouchHandling::getTouchActivation(){
	return touchActivation;
}
