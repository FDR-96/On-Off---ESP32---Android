/*
#    Control On/Off 
#    
#    Version del programa: 1.3.1
#    Copyright © 2021 FDR-96
#    Copyright © 2021 ADICHIP
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h >
#include <WiFiManager.h>
#include <FirebaseESP8266.h>

const int PIN_ON = 6;

#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxx"
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define PIN_ENCENDER (D2)
FirebaseData fbdo;

boolean data = false;


void setup()
{
  Serial.begin(115200);
  pinMode(PIN_ENCENDER, OUTPUT);
  // Creamos una instancia de la clase WiFiManager
  WiFiManager wifiManager;
 
  // Descomentar para resetear configuración
  //wifiManager.resetSettings();
 
  // Cremos AP y portal cautivo
  wifiManager.autoConnect("ESP8266Temp");
 
  Serial.println("Ya estás conectado");
   //3. Set your Firebase info
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  //5. Try to set int data to Firebase
  //The set function returns bool for the status of operation
  //fbdo requires for sending the data
  if(Firebase.setBool(fbdo, "/ESP8266-Proyect/Control-OnOff/Encender", true))
  {
    //Success
     Serial.println("Esta funcionando correctamente");

   }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in setInt, ");
    Serial.println(fbdo.errorReason());
  }
  //fbdo requires for sending the data
  if(Firebase.setBool(fbdo, "/ESP8266-Proyect/Control-OnOff/Encender", true))
  {
    //Success
     Serial.println("Esta funcionando correctamente");

   }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in setInt, ");
    Serial.println(fbdo.errorReason());
  }


  
}
 
void loop() {
  
  if(Firebase.getBool(fbdo, "/ESP8266-Proyect/Control-OnOff/Encender"))
  {
    data = fbdo.boolData();
  }else{
    Serial.print("Error al obtener el booleano, ");
    Serial.println(fbdo.errorReason());
  }
 
  if(data){
    digitalWrite(PIN_ENCENDER, HIGH);
    delay(40L);
    digitalWrite(PIN_ENCENDER, LOW);
    while(data){
      if(Firebase.setBool(fbdo, "/ESP8266-Proyect/Control-OnOff/Encender", false))
      {
        data = false;
        Serial.println("Se encendio la PC");
      }
    }
  }

}