#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#define USE_EPAPER



#include <serial_cmds.h>
#include <homewifi.h>

#ifdef USE_EPAPER
  #include <displayinit.h>
  #include <displaydemo.h>
#endif

#include <locadcell.h>
#include <humidity.h>

#ifdef USE_EPAPER
  #include <output_display.h>
#endif


#include <neoled.h>
#include <remotework.h>
#include <webfrontend.h>






void setup()
{
  EEPROM.begin(512);
  LED_setup();
  Serial.begin(115200);
  delay(1000);
  wifi_setup();
  SetupBalances();
  Serial.println();
#ifdef USE_EPAPER
  ePaper_setup();
#endif
  SerialCommandSetup();
  Serial.println("setup done");
#ifdef USE_EPAPER
  InfoPrintLn("Setup done");
#endif
  bme_setup();

PaintWeights();
//PaintDev();
}

void loopx(){
  //scan();
}

void loop()
{
  wifi_loop();
  sCmd.readSerial();
  
#ifdef USE_EPAPER
  PaintWeights();
#endif
  const int serialPrintInterval = 1500; //increase value to slow down serial print activity
  // get smoothed value from the dataset:
  ReadLoadCells();
    if (millis() > t + serialPrintInterval) {
      t = millis();
        bme_loop(); 

      
      PublishWeights();
    }
  

}

// note for partial update window and setPartialWindow() method:
// partial update window size and position is on byte boundary in physical x direction
// the size is increased in setPartialWindow() if x or w are not multiple of 8 for even rotation, y or h for odd rotation
// see also comment in GxEPD2_BW.h, GxEPD2_3C.h or GxEPD2_GFX.h for method setPartialWindow()

