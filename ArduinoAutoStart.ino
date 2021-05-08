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
int relayPin = 1;
int led = 2;
int neutralSwitch = 3;
//clutch switch only for manual 
//cars, set to HIGH in loop function
int clutchRelay = 4;
//relay to ignition switch to 
//close ignition circuit and
//start fuel pump and ecu
int ignitionSwitch = 5;
//setting engine input switch
// as analog input
int engineStarted = A0;

RH_ASK rf_driver;
void setup() 
{
  //initializing rf driver
  rf_driver.init();
  pinMode(relayPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(neutralSwitch, INPUT);
  pinMode(clutchRelay, OUTPUT);
  pinMode(ignitionSwitch, OUTPUT);
  //setting baud rate
  Serial.begin(9600);
}
//setting voltage to start engine at
//(voltage = 5 / 1023)
//1023 = 5 volts, 0 = 0 volts
int voltage = 500;
void loop() 
{
 
  //setting expected message buffer size
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  //if reciever recieved start payload
  if(rf_driver.recv(buf, &buflen))
  {
    //if engine is not running, start engine
    if(analogRead(engineStarted) < voltage)
    {
      Serial.println("Starting Car Operations");
      //opening ignition switch
      digitalWrite(ignitionSwitch, HIGH);
      //wait 2 seconds for fuel pump
      delay(2000);
      //send power to starter relay
      //for 3 seconds to crank car
      digitalWrite(relayPin, HIGH);
      delay(3000);
      digitalWrite(relayPin, LOW);
      Serial.println("Completed Car Start Operations");
    }
    else
    {
      Serial.println("Engine is running!");
    }
  }
  
}
