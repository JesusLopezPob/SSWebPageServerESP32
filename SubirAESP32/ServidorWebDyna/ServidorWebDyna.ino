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

void IRAM_ATTR isrLimitSwitch0() { limitTriggered[0] = true; }
void IRAM_ATTR isrLimitSwitch1() { limitTriggered[1] = true; }
void IRAM_ATTR isrLimitSwitch2() { limitTriggered[2] = true; }
void IRAM_ATTR isrLimitSwitch3() { limitTriggered[3] = true; }
void IRAM_ATTR isrLimitSwitch4() { limitTriggered[4] = true; }
void IRAM_ATTR isrLimitSwitch5() { limitTriggered[5] = true; }
void IRAM_ATTR isrLimitSwitch6() { limitTriggered[6] = true; }

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
  InitconfigDXL();
  delay(100);
  
  Serial.println("Configuracion completa."); 
   for (int p = 0; p < 4; p++) {
    Serial.println(servoActivo[p]);
 }
  //incializar el Server
  server_init();

  //inicializamos los sensores 

    for (int i = 0; i < 7; i++) {
    pinMode(Finalswitch[i], INPUT_PULLUP); 

  }

    // Asignar interrupciones a los limites de carrera 
  attachInterrupt(digitalPinToInterrupt(Finalswitch[0]), isrLimitSwitch0, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[1]), isrLimitSwitch1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[2]), isrLimitSwitch2, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[3]), isrLimitSwitch3, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[4]), isrLimitSwitch4, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[5]), isrLimitSwitch5, FALLING);
  attachInterrupt(digitalPinToInterrupt(Finalswitch[6]), isrLimitSwitch6, FALLING);


 }

  



void loop() {
  // put your main code here, to run repeatedly:
  
if (ejecutandoSecuencia) {

  //iniciar secuencia
    if (!puntoEnEjecucion) {
      // Saltar servos inactivos o sin puntos en este índice
      while (currentServo < MAX_SERVOS && 
             (!servoActivo[currentServo] || currentPoint >= servos[currentServo].contadorPuntos)) {
        Serial.printf("Servo %d inactivo o sin punto, saltando...\n", currentServo+1);
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
        Serial.print(currentServo+1);
        Serial.print(" a ");
        Serial.print(val);
        Serial.print(" ");
        Serial.println(typ);
        
        //dxl.setPortProtocolVersion(servos[currentServo]. protocolo);

        DXL_SERIAL.begin(currentBaud, SERIAL_8N1, RX_PIN, TX_PIN);
        dxl.begin(currentBaud);

         /*
        // Solo cambiar baudrate si es diferente
        static int baudActual = -1;
        if (currentBaud != baudActual) {
          Serial.printf("Cambiando baudrate a %d\n", currentBaud);
          DXL_SERIAL.begin(currentBaud, SERIAL_8N1, RX_PIN, TX_PIN);
          dxl.begin(currentBaud);
          delay(20);
          baudActual = currentBaud;
        }
        */
        
        moveDxl(currentServo, typ, val,0);
        puntoEnEjecucion = true;
      }
    } else {
      // Esperar que el servo actual llegue a la posición objetivo
      int id = servos[currentServo].id;
      if (servos[currentServo].puntos[currentPoint].tipo == "angle"){
        
        int currentPos = dxl.getPresentPosition(id, UNIT_DEGREE);
        int targetPos = servos[currentServo].puntos[currentPoint].valorPosicion;
  
        if (abs(currentPos - targetPos) <= angleTolerance ) {
          Serial.print("Servo ");
          Serial.print(currentServo+1);
          Serial.print(" llegó al punto ");
          Serial.println(currentPoint);
  
  
          currentServo++;
          puntoEnEjecucion = false;
        }
        
        if (limitSwitchActivado(currentServo)) {
        
          dxl.setGoalPosition(id, currentPos ); 
          dxl.writeControlTableItem(PROFILE_VELOCITY, id, 0);
          limitSwitchClear( currentServo);
          Serial.print("Servo ");
          Serial.print(currentServo+1);
          Serial.println(" Interrupido ");
          dxl.writeControlTableItem(PROFILE_VELOCITY,id,servos[currentServo].V);
           
          currentServo++;
          puntoEnEjecucion = false;
      }
        
      }else {
        
        int currentPos = dxl.getPresentPosition(id);
        int targetPos = servos[currentServo].puntos[currentPoint].valorPosicion;
  
        if (abs(currentPos - targetPos) <= tolerance ) {
          Serial.print("Servo ");
          Serial.print(currentServo+1);
          Serial.print(" llegó al punto ");
          Serial.println(currentPoint);
  
  
          currentServo++;
          puntoEnEjecucion = false;
        }

        if (limitSwitchActivado(currentServo)) {
        
          dxl.setGoalPosition(id, currentPos ); 
          dxl.writeControlTableItem(PROFILE_VELOCITY, id, 0);
          limitSwitchClear( currentServo);
          Serial.print("Servo ");
          Serial.print(currentServo+1);
          Serial.println(" Interrupido ");
          dxl.writeControlTableItem(PROFILE_VELOCITY,id,servos[currentServo].V);
        
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
  
      if (abs(currentPos - targetPos) <= angleTolerance ) {
        Serial.print("Servo ");
        Serial.print(indexSimple+1);
        Serial.println(" termino de moverse ");
        moveSimple=false;
        
      }
      if (limitSwitchActivado(indexSimple)) {
        
        dxl.setGoalPosition(id, indexSimple ); 
        dxl.writeControlTableItem(PROFILE_VELOCITY, id, 0);
        limitSwitchClear( currentServo);
        Serial.print("Servo ");
        Serial.print(indexSimple+1);
        Serial.println(" Interrupido ");
        dxl.writeControlTableItem(PROFILE_VELOCITY,id,servos[indexSimple].V);
        moveSimple=false;
      }
      
    }else {

      int currentPos = dxl.getPresentPosition(id);
      int targetPos = posSimple;
      //Serial.printf("Posicion objetivo →  %d,Posicion actual →  %d \n",targetPos, currentPos);
  
      if (abs(currentPos - targetPos) <= tolerance ) {
        Serial.print("Servo ");
        Serial.print(indexSimple+1);
        Serial.println(" termino de moverse ");
        moveSimple=false;
        
      }
        if ( limitSwitchActivado(indexSimple)) {
        dxl.setGoalPosition(id, currentPos ); 
        dxl.writeControlTableItem(PROFILE_VELOCITY, id, 0);
        limitSwitchClear( indexSimple);
        Serial.print("Servo ");
        Serial.print(indexSimple+1);
        Serial.println(" Interrupido ");
        dxl.writeControlTableItem(PROFILE_VELOCITY,id,servos[indexSimple].V);
        
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
    events.send( scanResultsJSON(scanDXL, MAX_SERVOS).c_str(), "SCAN" , millis());

    for (int i=0; i<MAX_SERVOS; i++){
      String ServoIndex=String(i+1);
      String evento = "chanceIcon" + String(i+1);
      if (scanDXL[i].id != -1) {
          Serial.print("Servo ");
          Serial.print(i+1);
          Serial.println("");
          IndConfigDXL(i);
          String flag=  String(servoActivo[i]); 

          events.send( chanceIconJSON(ServoIndex,flag).c_str(), evento.c_str(), millis());
          
      }else{
          Serial.print("Servo ");
          Serial.print(i+1);
          Serial.println(" no encontrado");
          servoActivo[i]=false;
          String flag=  String(servoActivo[i]); 
          events.send( chanceIconJSON(ServoIndex,flag).c_str(), evento.c_str(), millis());
        continue;
      }
    }
  
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
