#pragma once
#include <HX711_ADC.h>
#include <EEPROM.h>


#define HX1_SCK  48
#define HX1_DAT  45


//const int HX_DAT[] = {2, 3, 4, 5};  // Example pins, adjust as per your setup
//const int HX_SCK[] = {6, 7, 8, 9};  // Example pins, adjust as per your setup

//const int HX_DAT[] = {45};  // Example pins, adjust as per your setup
//const int HX_SCK[] = {48};  // Example pins, adjust as per your setup

const int HX_DAT[] = {5,7,16,18};  // Example pins, adjust as per your setup
const int HX_SCK[] = {4,6,15,17};  // Example pins, adjust as per your setup

//const int HX_SCK[] = {4,6,15,17};  // Example pins, adjust as per your setup
//const int HX_DAT[] = {5,7,16,18};  // Example pins, adjust as per your setup

//const int NUM_LOAD_CELLS = 1;
const int NUM_LOAD_CELLS = 4;



HX711_ADC *loadCells[NUM_LOAD_CELLS];


//HX711_ADC LoadCell_1(HX1_DAT, HX1_SCK);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

float Weight1 = 0;
float Weight2 = 0;
float Weight3 = 0;

float Weights[NUM_LOAD_CELLS];
int WeightInG[NUM_LOAD_CELLS];
float TaraOffSet[NUM_LOAD_CELLS];
float ConvFactor[NUM_LOAD_CELLS];


#define EEPROM_ADDR_WEIGHT1 0
#define EEPROM_ADDR_WEIGHT2 sizeof(float)
#define EEPROM_ADDR_WEIGHT3 2*sizeof(float)
#define EEPROM_ADDR_WEIGHT4 3*sizeof(float)
#define EEPROM_ADDR_TARA1 4*sizeof(float)
#define EEPROM_ADDR_TARA2 5*sizeof(float)
#define EEPROM_ADDR_TARA3 6*sizeof(float)
#define EEPROM_ADDR_TARA4 7*sizeof(float)
#define EEPROM_ADDR_CALOFF1 8*sizeof(float)
#define EEPROM_ADDR_CALOFF2 9*sizeof(float)
#define EEPROM_ADDR_CALOFF3 10*sizeof(float)
#define EEPROM_ADDR_CALOFF4 11*sizeof(float)

//   AddWeight = (NUM - 1) * sizeof(float)
//   AddTara = (NUM + 3) * sizeof(float)
//   AddCalOff = (NUM + 7) * sizeof(float)





void TaraBalance( int BalanceNo){
    long _offset = 0;
    loadCells[BalanceNo -1]->tare();
    _offset = loadCells[BalanceNo -1]->getTareOffset();
    int AddTara = (BalanceNo + 3) * sizeof(float);
    EEPROM.put(AddTara, _offset);
    EEPROM.commit();
    loadCells[BalanceNo -1]->setTareOffset(_offset);
}

void LoadTaras(){
    long _offset = 0;
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
        int AddTara = (i + 4) * sizeof(float);
        
        EEPROM.get(AddTara,_offset);
        TaraOffSet[i] = _offset;
        if(_offset != 0) loadCells[i]->setTareOffset(_offset);
         _offset = 0;
    }
}

void LoadCalibrations(){
    int AddCalOff = 0;
    float newCalibrationValue;
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
        AddCalOff = (i + 8) * sizeof(float);
        EEPROM.get(AddCalOff, newCalibrationValue);
        ConvFactor[i] = newCalibrationValue;
        if(newCalibrationValue < 1) newCalibrationValue = 0;
        loadCells[i]->setCalFactor(newCalibrationValue);
    }
}


void CalibrateBalance(int BalanceNo){
    int AddCalOff = (BalanceNo + 7) * sizeof(float);
    
    int Chan = BalanceNo - 1;
    TaraBalance(BalanceNo);
    loadCells[Chan]->setCalFactor(1.0); 
    while (!loadCells[Chan]->update());
    Serial.println("***");
    Serial.println("Start calibration:");
    Serial.println("Place the load cell an a level stable surface.");
    Serial.println("Remove any load applied to the load cell.");
    Serial.println("Send 't' from serial monitor to set the tare offset.");

    boolean _resume = false;
    while (_resume == false) {
        loadCells[Chan]->update();
        if (Serial.available() > 0) {
        if (Serial.available() > 0) {
            char inByte = Serial.read();
            if (inByte == 't') loadCells[Chan]->tareNoDelay();
        }
        }
        if (loadCells[Chan]->getTareStatus() == true) {
        Serial.println("Tare complete");
        _resume = true;
        }
    }    


    Serial.println("Now, place your known mass on the loadcell.");
    Serial.println("Then send the weight of this mass (i.e. 100.0) from serial monitor.");

    float known_mass = 0;
    _resume = false;
    while (_resume == false) {
        loadCells[Chan]->update();
        if (Serial.available() > 0) {
        known_mass = Serial.parseFloat();
        if (known_mass != 0) {
            Serial.print("Known mass is: ");
            Serial.println(known_mass);
            _resume = true;
        }
        }
    }


    loadCells[Chan]->refreshDataSet(); //refresh the dataset to be sure that the known mass is measured correct
    float newCalibrationValue = loadCells[Chan]->getNewCalibration(known_mass); //get the new calibration value

    Serial.print("New calibration value has been set to: ");
    Serial.print(newCalibrationValue);
    Serial.println(", use this as calibration value (calFactor) in your project sketch.");
    Serial.print("Save this value to EEPROM adress ");
    Serial.print(calVal_eepromAdress);
    Serial.println("? y/n");


  _resume = false;
  while (_resume == false) {
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 'y') {

        EEPROM.put(AddCalOff, newCalibrationValue);
        EEPROM.commit();
        EEPROM.get(AddCalOff, newCalibrationValue);
        Serial.print("Value ");
        Serial.print(newCalibrationValue);
        Serial.print(" saved to EEPROM address: ");
        Serial.println(calVal_eepromAdress);
        _resume = true;

      }
      else if (inByte == 'n') {
        Serial.println("Value not saved to EEPROM");
        _resume = true;
      }
    }
  }
  Serial.println("End calibration");
  Serial.println("***");
  Serial.println("To re-calibrate, send 'r' from serial monitor.");
  Serial.println("For manual edit of the calibration value, send 'c' from serial monitor.");
  Serial.println("***");
}



int WaitCycles = 0;
int CycleDelay = 5;
void ReadLoadCells()
{
  static boolean newDataReady[] = {0,0,0,0};
    float val = 0;
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
        if (loadCells[i]->update()) newDataReady[i] = true;
        if(newDataReady[i]){
            
            if(WaitCycles < CycleDelay){
                WaitCycles++;
            }else{
            
            val = loadCells[i]->getData();
            Weights[i] = val;
            WeightInG[i] = round(val); 
            newDataReady[i] = 0;

            }
        }
    }  
}




void SetupBalances(){
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = false; //set this to false if you don't want tare to be performed in the next step


    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
        loadCells[i] = new HX711_ADC(HX_DAT[i], HX_SCK[i]); //  LoadCell(HX_DAT[i], HX_SCK[i]);
        loadCells[i]->setSamplesInUse(2);
        loadCells[i]->setGain(128);
        loadCells[i]->begin();

        if (loadCells[i]->getTareTimeoutFlag()) {
            Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
            while (1);
        }
        loadCells[i]->setCalFactor(-656.51);


        if(i == 0) loadCells[0]->setCalFactor(-656.51);
        if( i == 1) loadCells[1]->setCalFactor(-761.31); 
        ConvFactor[i] = loadCells[i]->getCalFactor();

        Weights[i] = 0;
        WeightInG[i] = 0;
    }
    LoadTaras();
    //LoadCalibrations();  
}