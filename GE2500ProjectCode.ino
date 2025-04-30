#include <Stepper.h>

// Button and LED Pins
const int whiteButtonPin = 4;  // White button
const int whiteLedPin = 5;     // White LED
const int redButtonPin = 2;    // Red button
const int redLedPin = 3;       // Red LED
const int blueLedPin = 6;
const int blueButtonPin = 7;
const int greenLedPin = A0;
const int greenButtonPin = 12;
const int resetButton = 13; // works with pin 
const int whiteButtonPin2 = A1;  // White button
const int whiteLedPin2 = A2; 

// states of LED
int whiteLedState = LOW;
int redLedState = LOW;
int blueLedState = LOW;
int greenLedState = LOW;
int whiteLedState2 = LOW;

// last states
int lastWhiteButtonState; // default HIGH because of INPUT_PULLUP
int lastRedButtonState;
int lastBlueButtonState;
int lastGreenButtonState;
int lastWhiteButtonState2;
int lastResetState;

// stepper motor config
const int stepsPerRevolution = 2048;  // full 360-degree rotation
const int rpm = 15;                    // motor speed

// initialize stepper on pins 8-11 (IN1, IN3, IN2, IN4)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() 
{

  delay(100);
  Serial.begin(9600);
  
  // LED pins to OUTPUT
  pinMode(whiteLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(whiteLedPin2, OUTPUT);

  // button pins to INPUT
  pinMode(whiteButtonPin, INPUT_PULLUP);  // internal pull-up resistor
  pinMode(redButtonPin, INPUT_PULLUP);   
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(whiteButtonPin2, INPUT_PULLUP);

  // initiallize all buttons to OFF
  digitalWrite(whiteLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(whiteLedPin2, LOW);

  // read state of initial button
  lastWhiteButtonState = digitalRead(whiteButtonPin);
  lastRedButtonState = digitalRead(redButtonPin);
  lastBlueButtonState = digitalRead(blueButtonPin);
  lastGreenButtonState = digitalRead(greenButtonPin);
  lastWhiteButtonState2 = digitalRead(whiteButtonPin2);
  lastResetState = digitalRead(resetButton);

  myStepper.setSpeed(rpm);

}

void loop() 
{
  // read current button states
  int whiteState = digitalRead(whiteButtonPin);
  int redState = digitalRead(redButtonPin);
  int blueState = digitalRead(blueButtonPin);
  int greenState = digitalRead(greenButtonPin);
  int whiteState2 = digitalRead(whiteButtonPin2);
  int resetState = digitalRead(resetButton);

  // White Button Pressed/
  // toggle LED & Rotate Motor 
  // checks if button was pressed, button is currently pressed using pull-up where pressing button connects it to ground
  // lastWhite means button not pressed in previous iteration
  if (whiteState == LOW && lastWhiteButtonState == HIGH) { 
    // toggle state of button if high then low vise versa
    whiteLedState = !whiteLedState;
    digitalWrite(whiteLedPin, whiteLedState);
  
    myStepper.step(-stepsPerRevolution);  // rotate

    delay(200);  
  }

  // Red Button Pressed 
  // toggle LED & Rotate Motor 
  if (redState == LOW && lastRedButtonState == HIGH) {
    redLedState = !redLedState;
    digitalWrite(redLedPin, redLedState);
    
    myStepper.step(-stepsPerRevolution);  // rotate 

    delay(200); 
  }

   // Blue Button Pressed 
   // toggle LED & Rotate Motor 
  if (blueState == LOW && lastBlueButtonState == HIGH) {
    blueLedState = !blueLedState;
    digitalWrite(blueLedPin, blueLedState);
    
    myStepper.step(-stepsPerRevolution);  // rotate

    delay(200);
 
  }

  // Green Button Pressed 
   // toggle LED & Rotate Motor 
  if (greenState == LOW && lastGreenButtonState == HIGH) {
    greenLedState = !greenLedState;
    digitalWrite(greenLedPin, greenLedState);
    
    myStepper.step(-stepsPerRevolution);  // rotate

    delay(200);
  }

    // second white Button Pressed 
   // toggle LED & Rotate Motor 
  if (whiteState2 == LOW && lastWhiteButtonState2 == HIGH) {
    whiteLedState2 = !whiteLedState2;
    digitalWrite(whiteLedPin2, whiteLedState2);
    
    myStepper.step(stepsPerRevolution);  // rotate

    delay(200);
  }

   // turn off all LEDs if RESET pushed
  if (resetState == LOW && lastResetState == HIGH) 
  {
    whiteLedState = LOW;
    redLedState = LOW;
    blueLedState = LOW;
    greenLedState = LOW;
    whiteLedState2 = LOW;

    digitalWrite(whiteLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(whiteLedPin2, LOW);
  }
  // update the last button states
  lastWhiteButtonState = whiteState;
  lastRedButtonState = redState;
  lastBlueButtonState = blueState;
  lastGreenButtonState = greenState;
  lastWhiteButtonState2 = whiteState2;
  lastResetState = resetState;

}

