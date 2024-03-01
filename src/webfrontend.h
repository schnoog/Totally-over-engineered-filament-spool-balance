#pragma once
#include <ArduinoJson.h>
#include <homewifi.h>
#include <humidity.h>
#include <locadcell.h>
#include <web_html.h>
//BASEURL + "api/maxhum/" + newhum
//BASEURL + "api/minhum/" + newhum
//BASEURL + "api/mancontrol
//BASEURL + "api/autoontrol
//BASEURL + "api/pumps/" + 0/1;

//BASEURL + "api/emptyspool/" + spoolno + "/" + spooltara
//BASEURL + "api/tare/" + BalanceNo
//BASEURL + "api/calibrate/" + BalanceNo;

void generateJsonData(JsonDocument& doc) {
  JsonArray loadCells = doc.createNestedArray("LoadCells");

  for (int i = 0; i < NUM_LOAD_CELLS; i++) {
    JsonObject obj = loadCells.createNestedObject();
    obj["Weight"] = Weights[i];
    obj["WeightInG"] = WeightInG[i];
    obj["TaraOffSet"] = TaraOffSet[i];
    obj["ConvFactor"] = ConvFactor[i];
    obj["EmptySpool"] = EmptySpool[i];
  }
}


void handleDataRequest(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(NUM_LOAD_CELLS * 5 + 6)); // Adjust size accordingly

  generateJsonData(doc);

  doc["Humidity"] = Humidity;
  doc["Temperature"] = Temperature;
  doc["MinHum"] = MinHum;
  doc["MaxHum"] = MaxHum;
  doc["AutoControl"] = AutoContol;
  doc["PumpState"] = PumpState;

  serializeJson(doc, *response);
  request->send(response);
}




void setup_web_routes(){

    server.on("/api/data", HTTP_GET, handleDataRequest);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", PAGE_MAIN);
    });


    server.on("/a", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
    });

    server.on("/hia", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", "HUHU<hr>! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
    });

    server.on("/api/autocontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
        AutoContol = 1;
        request->send(200, "text/html", "/api/autocontrol");
    });

    server.on("/api/mancontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
        AutoContol = 0;
        request->send(200, "text/html", "/api/mancontrol");
    });

    server.on("/api/pumps/1", HTTP_GET, [](AsyncWebServerRequest *request) {
        pumps_on();
        request->send(200, "text/html", "/api/pumps/1");
    });    

    server.on("/api/pumps/0", HTTP_GET, [](AsyncWebServerRequest *request) {
        pumps_off();
        request->send(200, "text/html", "/api/pumps/0");
    });    

    server.on("^\\/api\\/tare\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int balance = newmax.toInt();
        TaraBalance(balance);
        request->send(200, "text/plain", "-tare-");
    });

    server.on("^\\/api\\/calibrate\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int balance = newmax.toInt();
        CalibrateBalance(balance);
        request->send(200, "text/plain", "-calibrate-");
    });


    server.on("^\\/api\\/maxhum\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        MaxHum = newmax.toInt();
        save_HumSettings();
        request->send(200, "text/plain", "-maxhum-");
    });

    server.on("^\\/api\\/minhum\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        MinHum = newmax.toInt();
        save_HumSettings();
        request->send(200, "text/plain", "-minhum-");
    });

    






}

