//ESP32 - WiFi - WEB SERVER con Dynamixel 
//Pagina con UI para el control de servos dynamixel
//Control de posicion, definicon de vel, acel y PID
//Ejecucion de secuencias para muñeca robotica
//Uso de servidorasíncrono, DNS, JSON, SPIFFS

#include <WiFi.h>                            //Biblioteca WiFi
#include <ESPAsyncWebServer.h>  //WebServer asíncrono
#include <Arduino_JSON.h>           //Manejo de datos JSON
#include <SPIFFS.h>                        //Sistema de archivos
#include <wifi_Dxl.hpp>         //Manejo de Modo WiFi
#include <Dynamixel2Arduino.h>
#include <spiffs_uli.hpp>                        //Sistema de archivos
#include "variables.h"          //Manejo de variables y constantes
#include "json.hpp"
#include "server.hpp"
#include "DxlConfig.hpp"


void setup() {
  // put your setup code here, to run once:
  //iniciar Serial
  Serial.begin(115200);


  //inciar WIFI
  wifi_AP_init(ssid,pass);
  delay(1000);
  
  // Acceder al SPIFFS
  spiffs_init();

   //configurar los servomotores
  //configDXL();
  
  //incializar el Server
  server_init();
  delay(100);


  

}

void loop() {
  // put your main code here, to run repeatedly:

}
