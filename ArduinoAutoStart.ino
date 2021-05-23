/*
 * This project is for starting a car with a 
 * gsm module. In its current state, it is 
 * set to function with a 433mhz transmitter
 * and reciever, just like the standard 
 * chevy car auto start system.
 * 
 * Date: 5/9/21
 * Author: KYGM
 */
 
#include<SPI.h>

//instance variables
int starterRelay = 4;
int led = 3;
int neutralSafety = 3;
//clutch switch only for manual 
//cars, set to HIGH in loop function
int clutchRelay = 0;
//relay to ignition switch to 
//close ignition circuit and
//start fuel pump and ecu
int ignitionRelay = 1;
//setting engine input switch
//as analog input
int engineStarted = A0;
int reciever = 5;

/*
 * Avoiding neutral switch as it 
 * may be unnescessary for automatic
 * vehicles. To implement, add if block
 * to handle neutral high reading from
 * switch.
 */

void setup() 
{
  pinMode(starterRelay, OUTPUT);
  pinMode(ignitionRelay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(neutralSafety, INPUT);
  pinMode(clutchRelay, OUTPUT);
  pinMode(reciever, INPUT);
  //setting baud rate
  Serial.begin(9600);
}
//setting voltage to start engine at
//(voltage = 5 / 1023)
//1023 = 5 volts, 0 = 0 volts
int voltage = 500;
void loop() 
{
 
  //if reciever start signal
  //check engine run status
  if(digitalRead(reciever) == HIGH);
  {
    //if engine is not running, begin start sequence
    if(analogRead(engineStarted) < voltage)
    {
      //if neutral switch is not on, ie car not 
      //in neutral, DO NOT START ENGINE
      if(digitalRead(neutralSafety) == HIGH)
      {
        Serial.println("Starting Car Operations");
        //opening ignition switch
        digitalWrite(ignitionRelay, HIGH);
        //wait 2 seconds for fuel pump
        fuelPumpLight();
        delay(2000);
        //send power to starter relay
        //for 3 seconds to crank car
        runLed(true);
        digitalWrite(starterRelay, HIGH);
        delay(3000);
        digitalWrite(starterRelay, LOW);
        runLed(false);
  
        if(analogRead(engineStarted) < voltage)
        {
          Serial.println("Error Starting Engine!");
          runError();
        }
        else
        {
          Serial.println("Completed Car Start Operations");
        }
      }
      else
      {
        Serial.println("Car Not in Neutral!");
        runError();
      }

    }
    //engine is already running
    else
    {
      Serial.println("Engine is running!");
      //let user know that engine is running
      engineRunning();
    }
  }//end start remote if block
  
}

//led functions
void engineRunning()
{
  //blink led 3 times to let user
  //know that engine is running
  
  int bk = 3;
  for(int x = 0; x < bk; x++)
  {
    digitalWrite(led, HIGH);
    delay(700);
    digitalWrite(led, LOW);
  }
}
void fuelPumpLight()
{
  digitalWrite(led, HIGH);
  delay(700);
  digitalWrite(led, LOW);
}
void runError()
{
  //blink led 5 times to let user
  //know that there is an error
  
  int bk = 5;
  for(int x = 0; x < bk; x++)
  {
    digitalWrite(led, HIGH);
    delay(700);
    digitalWrite(led, LOW);
  }
}
void runLed(bool on)
{
  if(on)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}
