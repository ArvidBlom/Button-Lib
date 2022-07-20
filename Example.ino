#include <ButtonLib.h>


buttonClass button1(3,false);
buttonClass button2(6,false);
buttonClass button3(7,false);


void func1(){
  Serial.println("Function 1");
}

void func2(){
  Serial.println("Function 2");
}

void func3(){
  Serial.println("Function 3");
}

void setup() {
  Serial.begin(8600);

  //attachRisingEdge, called on a rising edge
  //attachFallingEdge, called on a falling edge
  //attachSingleClick, called on a single click
  //attachDoubleClick, called on a double click
  //attachTrippleClick, called on a tripple click
  //attachSingleHold, called once when button is held
  //attachContinuousHold, called continuously when button is held
  //attachSingleNotHeld, called once when button is not held
  //attachContinuousNotHeld, called continuously when button is not held


  button1.attachRisingEdge(func1); //when button1 is pressed it calls func1
  button1.attachFallingEdge(func2); //when button1 is released it calls func1 again

  //Note that tripple clicking a button will not call the single and double click functions.
  button2.attachSingleClick(func1); //when button2 is clicked it calls func1 (on the buttons release)
  button2.attachDoubleClick(func2); //when button2 is double clicked it calls func2
  button2.attachTrippleClick(func3); //when button2 is tripple clicked it calls func3

  button3.attachContinuousHold(func1); //Once button3 has been held for more than 1000ms func1 will be called evertime tick() is called
  button3.attachSingleNotHeld(func2); //Once button3 is not being held anymore func2 will be called once
  


  
  

}

void loop() {
  
  //tick() has to be called every loop, it checks the level of the pins, keeps track of debouncing, calls funtions, sets flags etc
  button1.tick();
  button2.tick();
  button3.tick();


  if(button2.doubleClick){ //.doubleClick is a boolean that is true if the button was just double clicked
    Serial.println("Button 2 was just double clicked");
  }

  if(button3.rising){ //.doubleClick is a boolean that is true if the button was just double clicked
    Serial.println("Button 3 was just pushed down");
  }

  if(button3.falling){ //.doubleClick is a boolean that is true if the button was just double clicked
    Serial.println("Button 3 was just released");
  }
  

}
