void actuators(int state)
{
  digitalWrite(FUEL_MAIN_PIN, stateMatrix[state][FUEL_MAIN]);
  digitalWrite(FUEL_PRESTAGE_PIN, stateMatrix[state][FUEL_PRESTAGE]);
  digitalWrite(FUEL_PRESS_PIN, stateMatrix[state][FUEL_PRESS]);
  digitalWrite(ENGINE_PURGE_PIN, stateMatrix[state][ENGINE_PURGE]);
}

void manualActuate(int command)
{
  switch (command)
  {
    case 'a':
    digitalWrite(RS485_DIR_PIN, HIGH);
    mySerial.println("Engine Purge Open");
    digitalWrite(ENGINE_PURGE_PIN,1);
    break; 
    
    case 'z':
    digitalWrite(RS485_DIR_PIN, HIGH);
    mySerial.println("Engine Purge Close");
    digitalWrite(ENGINE_PURGE_PIN,0);
    break;
    
    case 'S':
    // LOX PRESS OPEN
    break;
    
    case 'X':
    // LOX PRESS CLOSE
    break;
    
    case 'D':
    // LOX VENT OPEN
    break;
    
    case 'C':
    // LOX VENT CLOSE
    break;
    
    case 'F':
    // INJECTOR CHILL OPEN
    break;
    
    case 'V':
    // INJECTOR CHILL CLOSE
    break;
    
    case 'G':
    // LOX MAIN OPEN
    break;
    
    case 'B':
    // LOX MAIN CLOSE
    break;
    
    case 'H':
    digitalWrite(FUEL_PRESS_PIN,1);
    break;
    
    case 'N':
    digitalWrite(FUEL_PRESS_PIN,0);
    break;
    
    case 'J':
    digitalWrite(FUEL_PRESTAGE_PIN,1);
    break;
    
    case 'M':
    digitalWrite(FUEL_PRESTAGE_PIN,0);
    break;
    
    case 'K':
    digitalWrite(FUEL_MAIN_PIN,1);
    break;
    
    case '<':
    digitalWrite(FUEL_MAIN_PIN,0);
    break;
    
    case '8':
    propFlowInhibit = true; 
    break;
    
    case '9':
    propFlowInhibit = false; 
    break;

    case '-':
    // Pre-stage
    break;

    case '=':
    // Main-stage
    break;

    case 8 ://Ascii for backspace
    // Prop Flow Inhibit On
    break;
    
    case 47://Ascii for back slash
    activatePurge = 1;  
    break;
    
    default:
    // Error checking 
    break;
  }
  
}

