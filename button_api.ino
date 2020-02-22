#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP.h>
#include <Wire.h>

// ssid and key
const char* ssid = "";
const char* password = "";

const char* host = "";

const int led = 2;
const int buttonPin = D1;

void setup() {
  // start serial connection for debugging
  Serial.begin(115200);
  Serial.println("");

  // initialise button input pin
  pinMode(D1, INPUT_PULLUP);

  // init wire lib
  Wire.pins(0,2);
  Wire.begin();

  // initialise LED to indicate connection to internet
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); // low is on
  
  // attempt to connect
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);

  // wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
    delay(250);
    Serial.print(".");
  }
  Serial.println("Connected");
  quickFlash(led);
}

void quickFlash(int pin) {
  for (int i = 0; i < 20; i++){
    digitalWrite(pin, LOW);
    delay(50);
    digitalWrite(pin, HIGH);
    delay(50);
  }
}

void buttonPressed() {
  // turn on led to indicate press was registared
  digitalWrite(led, LOW);
  
  // start http 
  HTTPClient http;

  Serial.print("Connecting to "); Serial.println(host);
  // open connection to server
  http.begin(host, 80, "/button/?status=pushed");
  Serial.print("Sending request");

  // request page
  int httpCode = http.GET(); 

  // httpCode will be negative on error
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  // close connection
  http.end();

  // turn off led
  digitalWrite(led, HIGH);
}

void loop() {
  if(digitalRead(buttonPin) == LOW){
    buttonPressed();
    delay(100);
  }
}
