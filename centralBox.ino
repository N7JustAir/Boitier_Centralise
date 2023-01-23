// INCLUDE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>*/

// DEFINE
#define CE 7
#define CSN 8
#define TUNNEL "PIPE1"
/*#define FIREBASE_HOST "host"
#define FIREBASE_AUTH "auth"
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"
#define USER_MAIL "mail"
#define USER_PASSWORD "password"*/


// INITIALISATION DES VARIABLES
RF24 radio(CE, CSN);
const byte address[6] = TUNNEL;
struct dataPackage {
  int boxID;
  int valueAirQuality;
  int valueCO;
};
dataPackage data;

// INITIALISATION DE FIREBASE
/*FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
config.host = FIREBASE_HOST;
config.api_key = FIREBASE_AUTH;
auth.user.email = USER_MAIL;
auth.user.password = USER_PASSWORD;
Firebase.begin(&config, &auth);
Firebase.reconnectWifi(true);*/


// CODE PRINCIPAL
void setup() {
  // Initialisation de la liaison série
  Serial.begin(9600);

  // Initialisation de l'émetteur
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Connexion au Wifi
  /*WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  // Connexion à Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);*/
}

void loop() {
  // Réception des données
  if (radio.available()) {
    radio.read(&data, sizeof(dataPackage));
    Serial.print("boxID: ");
    Serial.print(data.boxID);
    Serial.print(" - airQuality: ");
    Serial.print(data.valueAirQuality);
    Serial.print(" - CO: ");
    Serial.println(data.valueCO);

    // Push des valeurs vers Firebase
    /*FirebaseJson values;
    values.set("boxID", data.boxID);
    values.set("airQuality", data.valueAirQuality);
    values.set("CO", data.valueCO);
    values.set("timestamp", millis());
    if (Firebase.pushJSON(fbdo, "/Sensors/chambre/gaz/0/measures", values)) {
      Serial.println("Pushed : " + fbdo.pushName());
    } else {
      Serial.println("Error : " + fbdo.errorReason());
    }*/
  }
}