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

#include <Preferences.h>

Preferences prefs;


void setup() {
  // put your setup code here, to run once:
  //iniciar Serial
  Serial.begin(115200);




   //inciar WIFI
  wifi_AP_init(ssid,pass);
  //connectToWiFi();
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

  //iniciar secuencia
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
        int currentBaud=servos[currentServo].baudrate;

        Serial.print("moviendo servo ");
        Serial.print(currentServo);
        Serial.print(" a ");
        Serial.print(val);
        Serial.print(" ");
        Serial.println(typ);
        
        //dxl.setPortProtocolVersion(servos[currentServo]. protocolo);
        
        DXL_SERIAL.begin(currentBaud, SERIAL_8N1, RX_PIN, TX_PIN);
        dxl.begin(currentBaud);
        
        moveDxl(currentServo, typ, val,0);
        puntoEnEjecucion = true;
      }
    } else {
      // Esperar que el servo actual llegue a la posición objetivo
      int id = servos[currentServo].id;
      if (servos[currentServo].puntos[currentPoint].tipo == "angle"){
        
        int currentPos = dxl.getPresentPosition(id, UNIT_DEGREE);
        int targetPos = servos[currentServo].puntos[currentPoint].valorPosicion;
  
        if (abs(currentPos - targetPos) <= angleTolerance) {
          Serial.print("Servo ");
          Serial.print(currentServo);
          Serial.print(" llegó al punto ");
          Serial.println(currentPoint);
  
  
          currentServo++;
          puntoEnEjecucion = false;
        }
        
      }else {
        
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

//iniciar movimiento individual
if (moveSimple) {
  
    DXL_SERIAL.begin(baudSimple, SERIAL_8N1, RX_PIN, TX_PIN);
    dxl.begin(baudSimple);
    dxl.setPortProtocolVersion(protSimple);
    int id=IDSimple;
    if (typeSimple=="angle"){
      int currentPos = dxl.getPresentPosition(id,UNIT_DEGREE);
      int targetPos = posSimple;
      //Serial.printf("Posicion objetivo →  %d,Posicion actual →  %d \n",targetPos, currentPos);
  
      if (abs(currentPos - targetPos) <= angleTolerance) {
        Serial.print("Servo ");
        //Serial.print(currentServo);
        Serial.println(" termino de moverse ");
        moveSimple=false;
        
      }    
    }else {

      int currentPos = dxl.getPresentPosition(id);
      int targetPos = posSimple;
      //Serial.printf("Posicion objetivo →  %d,Posicion actual →  %d \n",targetPos, currentPos);
  
      if (abs(currentPos - targetPos) <= tolerance) {
        Serial.print("Servo ");
        //Serial.print(currentServo);
        Serial.println(" termino de moverse ");
        moveSimple=false;
        
      }
    }
    

      /*
    int current = dxl.readControlTableItem(PRESENT_CURRENT, id);
    int temp = dxl.readControlTableItem(PRESENT_TEMPERATURE, id);
    int error = dxl.readControlTableItem(HARDWARE_ERROR_STATUS, id);
    Serial.printf("Diagnóstico servo %d → Corriente: %d, Temperatura: %d°C, Error: 0x%02X\n", id, current, temp, error);
    delay(10);
    */
  
}



//iniciar escaneo

if (scanMode){
    int countServos =scanServoDxl();
    reorderScanDXL(scanDXL, countServos, modeloOrden, MAX_SERVOS); 
    events.send( scanResultsJSON(scanDXL, countServos).c_str(), "SCAN" , millis());
  
    //request->send(200, "text/plain", "OK");  // Enviar respuesta
    scanMode=false;
    
}



/*
//medicion de latencia
unsigned long t_actual = millis();
if (t_actual -  t_anterior >= t_sensado) {
  t_anterior = t_actual;
  if (events.count() > 0 && check ) {
    //Serial.println("chequeo de latencia");
    events.send("Latencia OK", "latencia", millis());
    check=false;
  }
}
*/

 
}
