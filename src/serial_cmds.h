#include <SerialCommand.h>
#include <locadcell.h>
SerialCommand sCmd;  

void Tare(){
  int aNumber;
  char *arg;
  Serial.println("We're in processCommand");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    Serial.print("Tare Balance Number: ");
    Serial.println(aNumber);
    TaraBalance(aNumber);
  }else{
    Serial.println("No arguments");
  }
}

void Cali(){
  int aNumber;
  char *arg;
  Serial.println("We're in processCommand");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    Serial.print("Calibrate Balance Number: ");
    Serial.println(aNumber);
    CalibrateBalance(aNumber);
  }else{
    Serial.println("No arguments");
  }
}


void SerialCommandSetup(){
  sCmd.addCommand("tare", Tare);
  sCmd.addCommand("cali",   Cali);         // Turns LED off
  sCmd.addCommand("loadCal",LoadCalibrations);
  sCmd.addCommand("loadTare",LoadTaras);
//  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
//  Serial.println("Ready");
}
