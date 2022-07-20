# Button-Lib
An Arduino library to handle buttons

I got really tired of implementing button functionality in my projects and couldnt find a library that did it the way i wanted to.

Basic functionality (I should probably add an aexample project huh...)
1. Create a "button object" pin number as input, and whetere it is active high or active low, button1 = buttonClass(pinNumber,activeHigh);
2. Attach callback functions. button1.attachDoubleClick(myFunction), each time the button is double clicked that function will be called. 
3. Each loop iteration call button1.tick(), this keeps track of all the flags, callbacks, debouncing etc
4. After youve called tick() you can also check the event flags manually, ie if button1.doubleClick is true then the button was just double clicked since the last time tick() was called.

If there is any interest in this library I'll probably add a better explanation along with some example code

Puss å kram!
