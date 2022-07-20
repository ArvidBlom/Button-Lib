
#include <Arduino.h>
#define ButtonLib_h

//Thingy that makes callback functions possible
extern "C" {
typedef void (*callbackFunction)(void);
}


class buttonClass{
    public:
        buttonClass(int pin, int active, bool pullupActive = true); //constructor

        //functions for attatching callbacks
        void attachRisingEdge(callbackFunction newFunction);
        void attachFallingEdge(callbackFunction newFunction);
        void attachSingleClick(callbackFunction newFunction);
        void attachDoubleClick(callbackFunction newFunction);
        void attachTrippleClick(callbackFunction newFunction);
        void attachSingleHold(callbackFunction newFunction);
        void attachContinuousHold(callbackFunction newFunction);
        void attachSingleNotHeld(callbackFunction newFunction);
        void attachContinuousNotHeld(callbackFunction newFunction);

        void tick(void); //the tick function that the user will be using
        void tick(bool level); //The level bool needs to be there to keep track of active high or active low

        //Booleans to keep track of which event was just triggered. to be used instead of or together with callback functions. 
        bool rising            = false;
        bool falling           = false;
        bool singleClick       = false;
        bool doubleClick       = false;
        bool trippleClick      = false;
        bool singleHold        = false;
        bool continuousHold    = false;
        bool singleNotHeld     = false;
        bool continuousNotHeld = false;
        bool toggled           = false;

        unsigned long millisHeld;     //number of millis that the button has been held, starts at 0ms when the button has been held for _holdMillis time
        unsigned long millisReleased; //number of millis that the button has been released, starts at 0ms when the button has been released for _holdMillis time


    private:
        int _pin; // hardware pin number.
        unsigned int _debounceMillis = 50; // number of millis for debounce times.
        unsigned int _holdMillis = 1000; // number of millis to count as hold.
        unsigned int _doubleClickMillis = 200; // max number of millis between rising edges of a double click.
        unsigned int _clickLengthMillis = 200; // max number of millis button can be held to count as a click
        int _buttonPressed;

        int _state = 0; // state can either be 0 or 1, 0 = button is not pressed, 1 button is pressed
        int _numClicks = 0; //counter for keeping track of the number of clicks
        unsigned long _riseTime; // time in millis of last rising edge
        unsigned long _fallTime; // time in millis of last falling edge
        
        //all callback functions are initiated to NULL
        callbackFunction _risingFunc            = NULL; //function to be called on a rising edge
        callbackFunction _fallingFunc           = NULL; //function to be called on a falling edge
        callbackFunction _singleClickFunc       = NULL; //function to be called on a single click
        callbackFunction _doubleClickFunc       = NULL; //function to be called on a double click
        callbackFunction _trippleClickFunc      = NULL; //function to be called on a tripple click
        callbackFunction _singleHoldFunc        = NULL; //function to be called once when button is held
        callbackFunction _continuousHoldFunc    = NULL; //function to be called continuously when button is held
        callbackFunction _singleNotHeldFunc     = NULL; //function to be called once when button is not held
        callbackFunction _continuousNotHeldFunc = NULL; //function to be called continuously when button is not held

        bool _singleHoldFunctionCalled    = false;
        bool _singleNotHeldFunctionCalled = false;
  
};