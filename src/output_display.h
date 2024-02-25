
int OldVal[NUM_LOAD_CELLS];

void PaintWights(){
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
//  display.setFont(&FreeMonoBold9pt7b);
//  display.setFont(&FreeMonoBold24pt7b);
  display.setFont(&FreeMonoBold18pt7b);
  display.setCursor(0, 0);
  display.println();
  int leftOffSet = 0;
  int TopOffSet = 180;
  int BalancePart = 100;
  bool bolRun = false;
  for (int i = 0; i < NUM_LOAD_CELLS; ++i) {  
      if(WeightInG[i] != OldVal[i]) bolRun = true;
  }

  if(bolRun){
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
      leftOffSet = i * BalancePart;

      display.setCursor(leftOffSet,TopOffSet);

  //    display.print("Balance ");
  //    display.println(i+1);
  //    display.println("--------------------------------");
      display.print(WeightInG[i]);
      display.print(" g");
      OldVal[i] = WeightInG[i];
  //   display.println("--------------------------------");
  //   display.println("--------------------------------");

  Serial.print("Balance ");
  Serial.println(i+1);
  Serial.println("--------------------------------");
  Serial.println(WeightInG[i]);
  Serial.println("--------------------------------");
  Serial.println("--------------------------------");

    }


    display.display(true); // full update
  }
}




void InfoPrint(const String& message) {
  Serial.print(message);
}

// Function to print information with a newline
void InfoPrintLn(const String& message) {
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
//  display.setFont(&FreeMonoBold9pt7b);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(0, 0);
  display.println();
  display.println(message);
  display.display(true); // full update
  Serial.println(message);
}

