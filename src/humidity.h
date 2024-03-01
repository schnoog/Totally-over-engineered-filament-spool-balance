#pragma once


float Humidity = 25.2;
float Temperature = 21.2;

int PumpPin1 = 47;
int PumpPin2 = 48;
int PumpState = 0;

float MinHum = 59.1;
float MaxHum = 61.0;

int AutoContol = 1;

#include <BME280I2C.h>
#include <Wire.h>

#define EEPROM_ADDR_MINHUM 12*sizeof(float)
#define EEPROM_ADDR_MAXHUM 13*sizeof(float)


void load_HumSettings(){
    float mtmp = 0;
    EEPROM.get(EEPROM_ADDR_MINHUM,mtmp);
    if(mtmp > 0.0){
        MinHum = mtmp;
    }
    EEPROM.get(EEPROM_ADDR_MAXHUM,mtmp);
    if(mtmp > 0.0){
        MaxHum = mtmp;
    }

}

void save_HumSettings(){
    EEPROM.put(EEPROM_ADDR_MINHUM, MinHum);
    EEPROM.commit();
    EEPROM.put(EEPROM_ADDR_MAXHUM, MaxHum);
    EEPROM.commit();
}

void set_MinHum(float NewMinHum){
    MinHum = NewMinHum;
    save_HumSettings();
}

void set_MaxHum(float NewMaxHum){
    MaxHum = NewMaxHum;
    save_HumSettings();
}


BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

void scan(){
Serial.println("\n Scanning I2C Addresses");
uint8_t cnt=0;
for(uint8_t i=0;i<0x7F;i++){
  Wire.beginTransmission(i);
  uint8_t ec=Wire.endTransmission(true); // if device exists on bus, it will aCK
  if(ec==0){ // Device ACK'd
    if(i<16)Serial.print('0');
    Serial.print(i,HEX);
    cnt++;
  }
  else Serial.print(".."); // no one answered
  Serial.print(' ');
  if ((i&0x0f)==0x0f)Serial.println();
  }
Serial.print("Scan Completed, ");
Serial.print(cnt);
Serial.println(" I2C Devices found.");
}

void bme_setupx(){
    //Wire.setPins(42,41);
     Wire.begin();
    pinMode(PumpPin1,OUTPUT);
    pinMode(PumpPin2,OUTPUT);
}


void pumps_on(){
    digitalWrite(PumpPin1,HIGH);
    digitalWrite(PumpPin2,HIGH);
    PumpState = 1;
}

void pumps_off(){
    digitalWrite(PumpPin1,LOW);
    digitalWrite(PumpPin2,LOW);
    PumpState = 0;
}


void bme_setup()
{
    pinMode(PumpPin1,OUTPUT);
    pinMode(PumpPin2,OUTPUT);



  Wire.begin();


  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

void printBME280Data
(
   Stream* client
)
{
   float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

   client->print("Temp: ");
   client->print(temp);
   Temperature = temp;
   client->print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   client->print("\t\tHumidity: ");
   client->print(hum);
   Humidity = hum;
   client->print("% RH");
   client->print("\t\tPressure: ");
   client->print(pres);
   client->println("Pa");

   //delay(1000);
}


void bme_loop()
{
   printBME280Data(&Serial);
   //delay(500);
   if(AutoContol == 1){
    if(Humidity > MaxHum) pumps_on();
    if(Humidity < MinHum) pumps_off();
   }
}