#pragma once
#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include <ESP32Ping.h>
#include <PubSubClient.h>


#include <credentials.h>

String hostname = "Filastation";


WiFiClient espClient;
PubSubClient client(espClient);
#include <remotework.h>
//WebServer server(80);
AsyncWebServer server(80);
#include <webfrontend.h>

unsigned long previousMillis = 0;
unsigned long interval = 30000;


IPAddress local_IP(192, 168, 178, 82);
// Set your Gateway IP address
IPAddress gateway(192, 168, 178, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 178, 1);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
IPAddress PingIP (192, 168, 178, 1); // The remote ip to ping
unsigned long pingInterval = 60000;
unsigned long lastPing = 0;

void callbackX(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}



unsigned long ota_progress_millis = 0;

void onOTAStart() {
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
  } else {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}



void ota_setup(){
//AsyncWebServerRequest 
//    server.on("/", []() {
//        server.send(200, "text/plain", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
//    });

  setup_web_routes();
  //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //  request->send(200, "text/html; charset=utf-8", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
  //});

  server.on("/hi", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html; charset=utf-8", "HUHU<hr>! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
  });


  ElegantOTA.begin(&server);    // Start ElegantOTA
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);
  server.begin();
  Serial.println("HTTP server started");
}

void ota_loop(){
    //server.handleClient();
    ElegantOTA.loop();
}

void mqtt_setup(){
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // Publish and subscribe
    client.publish(topic, "Hi, I'm ESP32 ^^");
    char subtopic[50]; // Adjust the size as needed
    snprintf(subtopic, sizeof(subtopic), "%s/command/", topic);


    client.subscribe(subtopic);
}

int ConnFail = 0;
void wifi_setup(){
   if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
   
    WiFi.mode(WIFI_STA); //Optional
    WiFi.setHostname(hostname.c_str()); //define hostnamen
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
        ConnFail++;
        if(ConnFail > 1000){
          ESP.restart();
        }
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    ota_setup();
    mqtt_setup();

}

int pingfail = 0;

void pingcheck(){
    bool ret = Ping.ping(PingIP);
    if(!ret){
      pingfail++;
      pingInterval  = 10000;
      if(pingfail > 5)
      ESP.restart();
    }else{
      pingInterval  = 60000;
    }
}


void wifi_loop(){
  


  unsigned long currentMillis = millis();

  // Check if it's time to execute the function
  if (currentMillis - lastPing >= pingInterval) {
    // Save the current time as the last execution time
    lastPing = currentMillis;
    
    // Call your function here
    pingcheck();
  }






  int wifi_retry = 0;
  while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
      wifi_retry++;
      Serial.println("WiFi not connected. Try to reconnect");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid,password);
      delay(100);
  }
  if(wifi_retry >= 5) {
      Serial.println("\nReboot");
      ESP.restart();
  }


    ota_loop();
    client.loop();
}