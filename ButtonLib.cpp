
#include "ButtonLib.h" //include the declaration for this class
#include <Arduino.h>

//Constructor
buttonClass::buttonClass(int pin, int activeLow, bool pullupActive){ 
	_pin 	  = pin; 
	_riseTime = millis();
	_fallTime = millis();

	if (activeLow) {_buttonPressed = LOW;} // the button connects the input pin to GND when pressed.
	else {_buttonPressed = HIGH;}// the button connects the input pin to VCC when pressed.
	
	if (pullupActive) {pinMode(pin, INPUT_PULLUP);}// use the given pin as input and activate internal PULLUP resistor.
	else {pinMode(pin, INPUT);}// use the given pin as input
} 

//Attaching callback functions to different events
void buttonClass::attachRisingEdge(callbackFunction newFunction){_risingFunc = newFunction;} 
void buttonClass::attachFallingEdge(callbackFunction newFunction){_fallingFunc = newFunction;} 
void buttonClass::attachSingleClick(callbackFunction newFunction){_singleClickFunc = newFunction;} 
void buttonClass::attachDoubleClick(callbackFunction newFunction){_doubleClickFunc = newFunction;} 
void buttonClass::attachTrippleClick(callbackFunction newFunction){_trippleClickFunc = newFunction;} 
void buttonClass::attachSingleHold(callbackFunction newFunction){_singleHoldFunc = newFunction;} 
void buttonClass::attachContinuousHold(callbackFunction newFunction){_continuousHoldFunc = newFunction;} 
void buttonClass::attachSingleNotHeld(callbackFunction newFunction){_singleNotHeldFunc = newFunction;} 
void buttonClass::attachContinuousNotHeld(callbackFunction newFunction){_continuousNotHeldFunc = newFunction;} 


void buttonClass::tick(void){if (_pin >= 0) {tick(digitalRead(_pin) == _buttonPressed);}} //This is the "tick" called by the user, it checks the state of the button and compares it to active low or not

void buttonClass::tick(bool activeLevel)
{
	unsigned long now = millis(); // current (relative) time in msecs.

	//reset all trigger booleans
	rising            = false;
	falling           = false;
	singleClick       = false;
	doubleClick       = false;
	trippleClick      = false;
	singleHold        = false;
	continuousHold    = false;
	singleNotHeld     = false;
	continuousNotHeld = false;
	toggled 		  = false;


	if (_state == 0) { // button is not pressed and is waiting for pin to be pressed.
        _singleHoldFunctionCalled = false;
		toggled = false; //public bool flag
		millisReleased = now - _fallTime - _holdMillis; //millis that the button has been released
		millisHeld 	   = 0; //millis that the button has been held
		
		//if button is not active and the time since the last falling edge is larger than holdmillis then activate the "notHeld" functions
        if ((!activeLevel) && ((unsigned long)(now - _fallTime) > _holdMillis)) { 
			
            if (_singleNotHeldFunctionCalled == false){ if(_singleNotHeldFunc){_singleNotHeldFunc();} singleNotHeld=true; _singleNotHeldFunctionCalled = true;}
			if (_continuousNotHeldFunc){_continuousNotHeldFunc();}
			continuousNotHeld = true;
        }

		//if button is not active and the time since the last falling edge is larger than _doubleClickMillis but smaller than holdmillis then trigger the "click"-functions
		if ((!activeLevel) && ((unsigned long)(now - _fallTime) > _doubleClickMillis) && ((unsigned long)(now - _riseTime) < _holdMillis)) { 
			if      ( _numClicks==1) { if(_singleClickFunc){_singleClickFunc();}   singleClick = true;  _numClicks=0;} //Set single click flag and call corresponding function if one is attached
			else if ( _numClicks==2) { if(_doubleClickFunc){_doubleClickFunc();}   doubleClick = true;  _numClicks=0;} //Set double click flag and call corresponding function if one is attached
			else if ( _numClicks==3) { if(_trippleClickFunc){_trippleClickFunc();} trippleClick = true; _numClicks=0;} //Set tripple click flag and call corresponding function if one is attached
		}

		//To make sure that _numClicks is reset to zero after _doubleClickMillis millis
		if ((!activeLevel) && ((unsigned long)(now - _fallTime) > _doubleClickMillis))  {_numClicks=0;} //if no button has been pushed in _doubleClickMillis time, then reset the number of clicks

		//If button goes from not being active last loop, to being active this loop then register a rising edge and a click, given that more than debounceMillis time has passed.
		if ((activeLevel) && ((unsigned long)(now - _fallTime) > _debounceMillis) )  {			
			_state     = 1; // pin is pressed
			_riseTime = now; // remember rise time
			rising = true; //bolean flag 
			if (_risingFunc){_risingFunc();}
						
			_numClicks = min(_numClicks+1,3);
		}
		
	} else if (_state == 1) { // button is pressed and waiting for pin to be released.
		_singleNotHeldFunctionCalled = false; //boolean flag reset for
		toggled = true; //public bool flag
		millisReleased = 0; //millis that the button has been released
		millisHeld 	 = now - _riseTime - _holdMillis; //millis that the button has been held

		//if button has been held for more than holdmillis millis then trigger "hold"-functions
        if ((activeLevel) && ((unsigned long)(now - _riseTime) > _holdMillis)) {
            if (_singleHoldFunctionCalled == false){if(_singleHoldFunc){_singleHoldFunc();} singleHold=true; _singleHoldFunctionCalled = true;}
			if (_continuousHoldFunc){_continuousHoldFunc();}
			continuousHold = true;
        }

		//if button has just been released then trigger falling edge functions, given that more than dbounce time has passed.
		if ((!activeLevel) && ((unsigned long)(now - _riseTime) > _debounceMillis)) {
			_state    = 0;
			_fallTime = now;
			falling = true;
			if (_fallingFunc){_fallingFunc();}
	
		}
	} 
} 