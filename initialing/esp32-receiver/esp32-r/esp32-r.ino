/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct message {
   int red;
   int green;
   int blue;
} message;
message myMessage;




void onDataReceiver(const uint8_t * mac, const uint8_t *incomingData, int len) {
   Serial.println("Message received.");
   // We don't use mac to verify the sender
   // Let us transform the incomingData into our message structure
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  Serial.print("Red:");
  Serial.println(myMessage.red); 
  Serial.print("Green:");
  Serial.println(myMessage.green);
  Serial.print("Blue:");
  Serial.println(myMessage.blue);
}

void setup() {
  Serial.begin(115200);

  // Wifi STA Mode
  WiFi.mode(WIFI_STA);
  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");
  
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
//  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
  // put your main code here, to run repeatedly:
}
