/*
 * This project is for starting a car with a 
 * gsm module. In its current state, it is 
 * set to function with a 433mhz transmitter
 * and reciever, just like the standard 
 * chevy car auto start system.
 */
 

#include <RH_ASK.h>
#include<SPI.h>

//instance variables
int starterRelay = 1;
int led = 2;
int neutralSwitch = 3;
//clutch switch only for manual 
//cars, set to HIGH in loop function
int clutchRelay = 4;
//relay to ignition switch to 
//close ignition circuit and
//start fuel pump and ecu
int ignitionRelay = 5;
//setting engine input switch
// as analog input
int engineStarted = A0;
int startRemote = 6;

RH_ASK rf_driver;
void setup() 
{
  //initializing rf driver
  rf_driver.init();
  pinMode(starterRelay, OUTPUT);
  pinMode(ignitionRelay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(neutralSwitch, INPUT);
  pinMode(clutchRelay, OUTPUT);
  pinMode(startRemote, INPUT);
  //setting baud rate
  Serial.begin(9600);
}
//setting voltage to start engine at
//(voltage = 5 / 1023)
//1023 = 5 volts, 0 = 0 volts
int voltage = 500;
void loop() 
{
 
  //if reciever recieved start signal
  if(digitalRead(startRemote) == HIGH);
  {
    //if engine is not running, begin start sequence
    if(analogRead(engineStarted) < voltage)
    {
      //if not in neutral, DO NOT START
      if(digitalRead(neutralSwitch) == LOW)
      {
        Serial.println("Starting Car Operations");
        //opening ignition switch
        digitalWrite(ignitionRelay, HIGH);
        //wait 2 seconds for fuel pump
        delay(2000);
        //send power to starter relay
        //for 3 seconds to crank car
        digitalWrite(starterRelay, HIGH);
        delay(3000);
        digitalWrite(starterRelay, LOW);
        Serial.println("Completed Car Start Operations");
      }
      //else dont start engine
      else
      {
        Serial.println("Car not in neutral!");
      }
    }
    //engine is already running
    else
    {
      Serial.println("Engine is running!");
    }
  }//end start remote if block
  
}
