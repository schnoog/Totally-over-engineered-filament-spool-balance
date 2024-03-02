
int OldVal[NUM_LOAD_CELLS];

void PaintWeights(){
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
//  display.setFont(&FreeMonoBold9pt7b);
//  display.setFont(&FreeMonoBold24pt7b);
  display.setFont(&FreeMonoBold18pt7b);
//  display.fillRect(0, 25, 400, 4, GxEPD_BLACK);    // X0Y0          X400Y0
//  display.fillRect(0, 55, 400, 4, GxEPD_BLACK);    //
//  display.fillRect(0, 175, 400, 4, GxEPD_BLACK);   //
//  display.fillRect(195, 0, 10, 300, GxEPD_BLACK);  // x300Y0        X400Y300


  display.fillRect(195, 100, 10, 200, GxEPD_BLACK); // Vert middle line
  display.fillRect(0, 95, 400, 10, GxEPD_BLACK); // Top / Middle
  display.fillRect(0, 195, 400, 10, GxEPD_BLACK);// Middle / Bottom

  display.setCursor(30, 25);
  display.print("Humidity: ");
  display.print(Humidity);
  display.println(" %");
  display.print("Temperature: ");
  display.print(Temperature);
  display.println( "°C");

  int leftOffSet = 0;
  int TopOffSet = 180;
  int BalancePart = 100;
  bool bolRun = false;
  int mtmp;
  int XOs[4] = {5,205,5,205};
  int YOs[4] = {110,110,210,210};

  for (int i = 0; i < NUM_LOAD_CELLS; ++i) {  
      if(WeightInG[i] != OldVal[i]) bolRun = true;
  }

  if(bolRun){
    display.setFont(&FreeMonoBold18pt7b);
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {
      leftOffSet = XOs[i];
      TopOffSet = YOs[i];

      display.setFont(&FreeMonoBold12pt7b);
      display.setCursor(leftOffSet,TopOffSet + 15);
      display.print("Spool: ");
      display.print(i+1);

      display.setFont(&FreeMonoBold18pt7b);
      display.setCursor(leftOffSet,TopOffSet + 50);
      mtmp = WeightInG[i];
      if(EmptySpool[i]> 0){
          mtmp = WeightInG[i] - EmptySpool[i];
      }

      display.print(mtmp);
      display.print(" g");
      if(EmptySpool[i]> 0){
        display.print("(T)");
      }

      OldVal[i] = WeightInG[i];

      display.setFont(&FreeMonoBold9pt7b);
      display.setCursor(leftOffSet,TopOffSet + 75);
      display.print("Tare: ");
      display.setFont(&FreeMono9pt7b);
      display.print(EmptySpool[i]);
      display.print(" g");
      


    }


    display.display(true); // full update
  }
}



void PaintWights(){
  int mtmp;
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
      mtmp = WeightInG[i];
      if(EmptySpool[i]> 0){
          mtmp = WeightInG[i] - EmptySpool[i];
      }


      display.print(mtmp);
      display.print(" g");
      if(EmptySpool[i]> 0){
        display.print("(T)");
      }


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






