// INCLUDE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// DEFINE
#define CE 7
#define CSN 8


// INITIALISATION DES VARIABLES
RF24 radio(CE, CSN);
const byte address[6] = "00001";
struct dataPackage {
  int valueAirQuality;
  int valueCO;
};
dataPackage data;


// CODE PRINCIPAL
void setup() {
  // Initialisation de la liaison série
  Serial.begin(9600);

  // Initialisation de l'émetteur
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Réception des données
  if (radio.available()) {
    radio.read(&data, sizeof(dataPackage));
    Serial.print("airQuality: ");
    Serial.print(data.valueAirQuality);
    Serial.print(" - CO: ");
    Serial.println(data.valueCO);
  }
}