#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <serial_cmds.h>
#include <homewifi.h>
#include <displayinit.h>
#include <displaydemo.h>
#include <locadcell.h>
#include <output_display.h>
#include <neoled.h>
#include <remotework.h>









void setup()
{
  EEPROM.begin(512);
  LED_setup();
  Serial.begin(115200);
  delay(1000);
  wifi_setup();
  SetupBalances();
  Serial.println();
  ePaper_setup();
  SerialCommandSetup();
  Serial.println("setup done");
  InfoPrintLn("Setup done");
}

void loop()
{
  wifi_loop();
  sCmd.readSerial(); 
  const int serialPrintInterval = 500; //increase value to slow down serial print activity
  // get smoothed value from the dataset:
  ReadLoadCells();
    if (millis() > t + serialPrintInterval) {
      t = millis();
      
      PaintWights();
      PublishWeights();
    }
  

}

// note for partial update window and setPartialWindow() method:
// partial update window size and position is on byte boundary in physical x direction
// the size is increased in setPartialWindow() if x or w are not multiple of 8 for even rotation, y or h for odd rotation
// see also comment in GxEPD2_BW.h, GxEPD2_3C.h or GxEPD2_GFX.h for method setPartialWindow()

