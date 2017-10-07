#include "stateMatrixHeader.h"
#include <SoftwareSerial.h>

// --- State Array Indicies ---
#define FUEL_MAIN       0
#define FUEL_PRESTAGE   1 
#define ENGINE_PURGE    2
#define FUEL_PRESS      3
#define TIME_EVAL       4
// ----------------------------


// ----------- Pins -----------
// SOLENOIDS
#define FUEL_MAIN_PIN       8
#define FUEL_PRESTAGE_PIN   9
#define FUEL_PRESS_PIN      10
#define ENGINE_PURGE_PIN    11


// PT's
#define PRESS_FUEL_TANK_PIN  A0
#define PRESS_FUEL_INJ_PIN   A1
// ----------------------------


// ------- Serial Comm --------
#define RS485_DIR_PIN       4
// ----------------------------


// Globals
int dataIn_bytes; 
char dataIn; 

int mode; 
int command; 
int state; 

bool propFlowInhibit;
bool activatePurge;

unsigned long loopStart;
unsigned long purgeTime;

SoftwareSerial mySerial(2,3); //RX TX

void setup() {
  analogReference(EXTERNAL); //Sets ref to 3.3V instead of 5, making analogRead more accurate. 

  pinMode(FUEL_MAIN_PIN, OUTPUT);
  pinMode(FUEL_PRESTAGE_PIN, OUTPUT);
  pinMode(ENGINE_PURGE_PIN, OUTPUT);

  pinMode(PRESS_FUEL_TANK_PIN, INPUT);
  pinMode(PRESS_FUEL_INJ_PIN, INPUT); 


  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  loopStart = millis(); 

  dataIn_bytes = mySerial.available(); 

  if(dataIn_bytes > 0) // If byte, read char
  {
    dataIn = mySerial.read(); // reads first byte
    
    digitalWrite(RS485_DIR_PIN, HIGH);
    mySerial.println(dataIn);
    
    switch (dataIn)
    {
      case '0':
        mode = 0; 
        break;
        
      case '1':
        mode = 1;
        digitalWrite(RS485_DIR_PIN, HIGH);
        mySerial.println("MANUAL MODE ENTERED");
        break;
      
      case '2':
        mode = 2;
        break;
      
      default:
        command = dataIn;
        break;    
    }
    // End of Switch
  
  }
  // End of (if(dataIn_bytes...

  if(activatePurge)
  {
    //firstEnterance = 1; 
    //purgeTime = millis 
    
  }

  switch (mode)
  {
    // SAFE MODE
    case 0:
      // manual mode w/ no option fuel prestage and fuel main 
      break;

    // MANUAL MODE
    case 1:

      if(command != 99)
      {
        manualActuate(command);
        // Null command 
        command = 99;
      }
      
      break; 
    
    // RUN MODE
    case 2: 
      actuators(state);
      // state transistion shit
      break; 

    default:
      Serial.println("Error: no mode");
      break;
  }
  // End of switch mode
}
// End of While
