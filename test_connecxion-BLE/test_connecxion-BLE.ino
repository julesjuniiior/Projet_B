/*
  Button LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED and another characteristic that
  represents the state of the button.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 4

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

BLEService componantsService("2023c"); // Créer un service BLE (avec l'adresse UUID= 2023c)

// create switch characteristic and allow remote device to read and write
// On permet à notre appareil central (Node-red) de pouvoir lire ces données et d'envoyer une notification si nécessaire
BLEStringCharacteristic resCharacteristic("2a50", BLERead | BLENotify, 20); 
BLEStringCharacteristic conCharacteristic("2a51", BLERead | BLENotify, 20); 
BLEStringCharacteristic dioCharacteristic("2a52", BLERead | BLENotify, 20); 
BLEStringCharacteristic ledCharacteristic("2a53", BLERead | BLENotify, 20); 

void setup() {
  Serial.begin(9600); 
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("comptage_component");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(componentsService);

  //  add the characteristics to the service
  componentsService.addCharacteristic(resCharacteristic);
  componentsService.addCharacteristic(conCharacteristic);
  componentsService.addCharacteristic(dioCharacteristic);
  componentsService.addCharacteristic(ledCharacteristic);

  // Ajouter le service
  BLE.addService(componentsService);

  // Définir des valeurs initiales contenues dans chaque caractéristiques (qui nous servira comme valeur initiale du comptage)
  resCharacteristic.writeValue("0");
  conCharacteristic.writeValue("0");
  dioCharacteristic.writeValue("0");
  ledCharacteristic.writeValue("0");

// start advertising
  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop() {

  // Gére les événements BLE
  BLE.poll();


    // On met a jour les valeurs de chaque caractéristiques
    resCharacteristic.writeValue(nbr_res);
    conCharacteristic.writeValue(nbr_con);
    dioCharacteristic.writeValue(nbr_diod);
    ledCharacteristic.writeValue(nbr_led);

}