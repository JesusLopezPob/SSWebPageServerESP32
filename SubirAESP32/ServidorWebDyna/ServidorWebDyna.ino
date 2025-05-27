//ESP32 - WiFi - WEB SERVER con Dynamixel 
//Pagina con HMI para el control de servos dynamixel
//Control de posicion, definicon de vel, acel y PID
//Ejecucion de secuencias para muñeca robotica
//Uso de servidor asíncrono, DNS, JSON, SPIFFS

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
#include <nvs_flash.h>

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
  configDXL();
  delay(100);
  Serial.println("Configuracion completa."); 
   for (int p = 0; p < 4; p++) {
    Serial.println(servoActivo[p]);
 }
  //incializar el Server
  server_init();

  

}

void loop() {
  // put your main code here, to run repeatedly:
  
if (ejecutandoSecuencia) {
    if (!puntoEnEjecucion) {
      // Saltar servos inactivos o sin puntos en este índice
      while (currentServo < MAX_SERVOS && 
             (!servoActivo[currentServo] || currentPoint >= servos[currentServo].contadorPuntos)) {
        Serial.printf("Servo %d inactivo o sin punto, saltando...\n", currentServo);
        currentServo++;
      }

      if (currentServo >= MAX_SERVOS) {
        // No quedan servos para mover en este punto, pasar al siguiente
        currentServo = 0;
        currentPoint++;
        Serial.print("Punto ");
        Serial.print(currentPoint);
        Serial.println(" completado (por saltar servos inactivos)");
        puntoEnEjecucion = false;

        if (currentPoint >= maxPoints) {
          Serial.println("Secuencia completada");
          ejecutandoSecuencia = false;
          currentPoint=0;

          // Limpiar trayectoria
          for (int i = 0; i < MAX_SERVOS; i++) {
            servos[i].contadorPuntos = 0;
            for (int j = 0; j < 10; j++) {
              servos[i].puntos[j].valorPosicion = 0.0;
              servos[i].puntos[j].tipo.clear();
            }
          }
        }
      } else if (currentServo < MAX_SERVOS && currentPoint < maxPoints) {
        // Enviar comando para mover servo actual
        int val = servos[currentServo].puntos[currentPoint].valorPosicion;
        String typ = servos[currentServo].puntos[currentPoint].tipo;

        Serial.print("moviendo servo ");
        Serial.print(currentServo);
        Serial.print(" a ");
        Serial.print(val);
        Serial.print(" ");
        Serial.println(typ);
        
        dxl.setPortProtocolVersion(servos[currentServo]. protocolo);
        moveDxl(currentServo, typ, val);
        puntoEnEjecucion = true;
      }
    } else {
      // Esperar que el servo actual llegue a la posición objetivo
      int id = servos[currentServo].id;
      int currentPos = dxl.getPresentPosition(id);
      int targetPos = servos[currentServo].puntos[currentPoint].valorPosicion;

      if (abs(currentPos - targetPos) <= tolerance) {
        Serial.print("Servo ");
        Serial.print(currentServo);
        Serial.print(" llegó al punto ");
        Serial.println(currentPoint);

        currentServo++;
        puntoEnEjecucion = false;
      }

        // Si terminamos con todos los servos de este punto, avanzar al siguiente punto
        if (currentServo >= MAX_SERVOS) {
          currentServo = 0;
          currentPoint++;
          Serial.print("Punto ");
          Serial.print(currentPoint);
          Serial.println(" completado");
        }

          if (currentPoint >= maxPoints) {
            Serial.println("Secuencia completada");
            ejecutandoSecuencia = false;
            currentPoint=0;

            // Limpiar trayectoria
            for (int i = 0; i < MAX_SERVOS; i++) {
              servos[i].contadorPuntos = 0;
              for (int j = 0; j < 10; j++) {
                servos[i].puntos[j].valorPosicion = 0.0;
                servos[i].puntos[j].tipo.clear();
              }
            }     
      }
    }
  }



    
}
