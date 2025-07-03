//Libreria de las funciones para  configuracion y control Dynamixel con ESP32
//derechos reservados ----

#pragma once
#include <Preferences.h>

extern Preferences prefs;  // Declaración: le dices al compilador que existe en otro lugar

//funcion para configurar a los servos Dynamixel para un inicio
void InitconfigDXL(){
  
  // Inicializa el puerto serial para Dynamixel
  DXL_SERIAL.begin(DXL_Baud, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(DXL_Baud);

  

      // eliminar la trayectoria y resetear el contadorPunto en caso de reseteo o alguna otra situacion
  for (int i = 0; i < MAX_SERVOS; i++) {
    servos[i].contadorPuntos=0;
    for (int j=0; j<10;j++){
      servos[i].puntos[j].valorPosicion=0.0;
      servos[i].puntos[j].tipo.clear();

    }
  }

    //inicializar las prefs 
  prefs.begin("my-config", false);  // false = lectura y escritura

  // Verificamos si ya fue inicializado antes
  bool initialized = prefs.getBool("initialized", false);
  
  for (int i = 0; i < 4; i++) {
    if (!initialized) {
      // 🟢 PRIMERA VEZ: usar valores por defecto y guardar
      servos[i].id        = (i == 0) ? 4 : i;
      servos[i].baudrate  = 1000000;
      servos[i].protocolo = (i == 1 || i == 2) ? 2.0 : 1.0;
      servos[i].P         = (i < 3) ? 120 : -1;
      servos[i].I         = (i < 3) ? 15 : -1;
      servos[i].D         = (i < 3) ? 1 : -1;
      servos[i].V         = (i < 3) ? 50 : 30;
      servos[i].A         = (i < 3) ? 50 : -1;

      // Guardar en memoria no volátil
      prefs.putUInt(("id" + String(i)).c_str(), servos[i].id);
      prefs.putUInt(("baud" + String(i)).c_str(), servos[i].baudrate);
      prefs.putFloat(("prot" + String(i)).c_str(), servos[i].protocolo);
      prefs.putInt(("P" + String(i)).c_str(), servos[i].P);
      prefs.putInt(("I" + String(i)).c_str(), servos[i].I);
      prefs.putInt(("D" + String(i)).c_str(), servos[i].D);
      prefs.putInt(("V" + String(i)).c_str(), servos[i].V);
      prefs.putInt(("A" + String(i)).c_str(), servos[i].A);
    } else {
      // 🔁 SUBSIGUIENTES VECES: cargar desde memoria
      servos[i].id        = prefs.getUInt(("id" + String(i)).c_str());
      servos[i].baudrate  = prefs.getUInt(("baud" + String(i)).c_str());
      servos[i].protocolo = prefs.getFloat(("prot" + String(i)).c_str());
      servos[i].P         = prefs.getInt(("P" + String(i)).c_str());
      servos[i].I         = prefs.getInt(("I" + String(i)).c_str());
      servos[i].D         = prefs.getInt(("D" + String(i)).c_str());
      servos[i].V         = prefs.getInt(("V" + String(i)).c_str());
      servos[i].A         = prefs.getInt(("A" + String(i)).c_str());
    }

    // Reset de trayectoria y contador
    servos[i].contadorPuntos = 0;
    for (int j = 0; j < 10; j++) {
      servos[i].puntos[j].valorPosicion = 0;
      servos[i].puntos[j].tipo.clear();
    }
  }

  // 🟢 Si es la primera vez, marcarlo
  if (!initialized) {
    prefs.putBool("initialized", true);
  }

  
  //config para MX106
  dxl.setPortProtocolVersion(1.0f);
  dxl.begin(servos[0].baudrate);
  DXL_SERIAL.begin(servos[0].baudrate, SERIAL_8N1, RX_PIN, TX_PIN);

  uint8_t id_Mx= servos[0].id;
  found=dxl.ping(id_Mx);
  if (!found) {
    Serial.print("Servo con ID ");
    Serial.print(id_Mx);
    Serial.println(" no detectado. Se omite configuración.");
    servoActivo[0]=false;
    String flag=  String(servoActivo[0]); 
    //events.send( chanceIconJSON("1",flag).c_str(), "chanceIcon1" , millis());
    //return;
  }else {
      dxl.torqueOff(id_Mx);
      dxl.setOperatingMode(id_Mx, OP_POSITION);
      dxl.writeControlTableItem(POSITION_P_GAIN, id_Mx, servos[0].P);
      dxl.writeControlTableItem(POSITION_I_GAIN, id_Mx, servos[0].I);
      dxl.writeControlTableItem(POSITION_D_GAIN, id_Mx, servos[0].D);

        // Configurar velocidad
      dxl.writeControlTableItem(PROFILE_VELOCITY, id_Mx, 50);
      dxl.writeControlTableItem(PROFILE_ACCELERATION, id_Mx, 30);
        
          
      dxl.torqueOn(id_Mx);
      int modelNumMX=dxl.getModelNumber(id_Mx);
      Serial.println("Servo MX " + String(id_Mx) + " configurado en posición (Protocolo 1.0). No Modelo:" + modelNumMX );
      servoActivo[0]=true;
      servos[0].model_number=modelNumMX;

      String flag=  String(servoActivo[0]); 
      //events.send( chanceIconJSON("1",flag).c_str(), "chanceIcon1" , millis());




  }


  //config para XM

  dxl.setPortProtocolVersion(2.0f);

  for  (int i=1; i<=2;i++){
    
    uint8_t id = servos[i].id;
    dxl.begin(servos[i].baudrate);
    DXL_SERIAL.begin(servos[i].baudrate, SERIAL_8N1, RX_PIN, TX_PIN);
    found=dxl.ping(id);
    if (!found) {
      Serial.print("Servo con ID ");
      Serial.print(id);
      Serial.println(" no detectado. Se omite configuración.");
      servoActivo[i]=false;

    }else {
        dxl.torqueOff(id);
        dxl.setOperatingMode(id, OP_POSITION);
        
        // Aplicar valores iniciales del PID y otros parámetros
        dxl.writeControlTableItem(POSITION_P_GAIN, id, servos[i].P);
        dxl.writeControlTableItem(POSITION_I_GAIN, id, servos[i].I);
        dxl.writeControlTableItem(POSITION_D_GAIN, id, servos[i].D);
        dxl.writeControlTableItem(PROFILE_VELOCITY, id, servos[i].V);
        dxl.writeControlTableItem(PROFILE_ACCELERATION, id, servos[i].A);

        dxl.torqueOn(id);
        int modelNumXM=dxl.getModelNumber(id);
        Serial.println("Servo " + String(id) + " configurado en posición (Protocolo 2.0).No Modelo:" +  modelNumXM);
        servoActivo[i]=true;
        servos[i].model_number=modelNumXM;

    }



    
    
  }

//==============================configuro para iniciar al AX18 ====================================// 

   dxl.setPortProtocolVersion(1.0f);
   dxl.begin(servos[3].baudrate);
   DXL_SERIAL.begin(servos[3].baudrate, SERIAL_8N1, RX_PIN, TX_PIN);
    if (dxl.ping(servos[3].id)) {
      Serial.println("Dynamixel AX18A encontrado y listo.");
  
      // Apagar torque
      if (!dxl.write(servos[3].id, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_OFF, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
        Serial.println("Error: No se pudo apagar el torque");
        return;
      }
      Serial.println("Torque apagado");
  
      // Configurar límites de ángulo
      if (!dxl.write(servos[3].id, AX_CW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT) ||
          !dxl.write(servos[3].id, AX_CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CCW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT)) {
        Serial.println("Error: No se pudo configurar el modo de operación");
        return;
      }
      Serial.println("Modo de operación configurado");
  
      // Configurar velocidad
      uint16_t speed = servos[3].V; 
      if (!dxl.write(servos[3].id,AX_MOVING_SPEED_ADDR, (uint8_t*)&speed, AX_MOVING_SPEED_ADDR_LEN, TIMEOUT)) {
        Serial.println("Error: No se pudo configurar la velocidad");
        return;
      }
      Serial.println("Velocidad de movimiento configurada");
  
      // Activar torque
      if (!dxl.write(servos[3].id, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_ON, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
        Serial.println("Error: No se pudo activar el torque");
        return;
      }
      Serial.println("Torque activado");
  
    } else {
      Serial.print("Servo con ID ");
      Serial.print(servos[3].id);
      Serial.println(" no detectado. Se omite configuración.");
      servoActivo[3]=false;
      return;
    }
//==============================fin de configuracion del AX18 ====================================// 

  // Regresar a protocolo 2.0 para servos 1 y 2
  dxl.setPortProtocolVersion(2.0f);
}

//configura un servo individualmente con los datos de ScanDXL
void IndConfigDXL(int index){
  
  int baudInd=scanDXL[index].baudrate;
  float protInd=(float)scanDXL[index].protocol;
  uint8_t idInd=scanDXL[index].id;
  
  DXL_SERIAL.begin(baudInd, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(baudInd);

  dxl.setPortProtocolVersion(protInd);
  
  bool encontrado=dxl.ping(idInd);
  if (!encontrado) {
    Serial.print("Servo con ID ");
    Serial.print(idInd);
    Serial.println(" no detectado. Se omite configuración.");
    
    servoActivo[index]=false;
    
    //return;
  }else {
      dxl.torqueOff(idInd);
      dxl.setOperatingMode(idInd, OP_POSITION);
      dxl.writeControlTableItem(POSITION_P_GAIN, idInd, servos[index].P);
      dxl.writeControlTableItem(POSITION_I_GAIN, idInd, servos[index].I);
      dxl.writeControlTableItem(POSITION_D_GAIN, idInd, servos[index].D);

      // Configurar velocidad
      dxl.writeControlTableItem(PROFILE_VELOCITY, idInd, servos[index].V);

       // Caso especial: index == 3 
        if (index == 3) {
          // Limites angulares
          if (!dxl.write(idInd, AX_CW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT) ||
              !dxl.write(idInd, AX_CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CCW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo configurar los límites de ángulo.");
            servoActivo[index] = false;
            return;
          }
      
          // Velocidad de movimiento
          uint16_t speed = servos[index].V;
          if (!dxl.write(idInd, AX_MOVING_SPEED_ADDR, (uint8_t*)&speed, AX_MOVING_SPEED_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo configurar la velocidad.");
            servoActivo[index] = false;
            return;
          }
      
          Serial.println("AX-18A: Velocidad de movimiento configurada.");
        } else{
          dxl.writeControlTableItem(PROFILE_ACCELERATION, idInd, servos[index].A);
      }

        
          
      dxl.torqueOn(idInd);
      int modelNum=dxl.getModelNumber(idInd);
      Serial.println("Servo con ID: " + String(idInd) + " configurado en modo posición . No Modelo:" + modelNum );
      servoActivo[index]=true;


      //escritura de los parametros
      servos[index].model_number=modelNum;
      servos[index].id          = idInd ;
      servos[index].baudrate    = baudInd;
      servos[index].protocolo   = protInd;

      prefs.putUInt(("id" + String(index)).c_str(), idInd);
      prefs.putUInt(("baud" + String(index)).c_str(), baudInd);
      prefs.putFloat(("prot" + String(index)).c_str(), protInd);

      



  }
  
}

//funcion  para reorganizar los resultados del scan en orden segun el orden que se muestra en la interfaz web
void reorderScanDXL(ServoInfo scanDXL[], int count_found,  int modeloOrden[], int ordenSize) {
  ServoInfo original[MAX_SERVOS];

/*
  //en caso que los # model los 2 XM sean lo mismo
  for (int i=0; i<4;i++){
    modeloOrden[i]=servos[i].id;
  }
*/
  // Copiar los resultados encontrados para no sobrescribir
  for (int i = 0; i < count_found; i++) {
    original[i] = scanDXL[i];
  }

  // Inicializar todos los elementos con valores inválidos (-1)
  for (int i = 0; i < ordenSize; i++) {
    scanDXL[i].id = -1;
    scanDXL[i].model_number = -1;
    scanDXL[i].protocol = -1;
    scanDXL[i].baudrate = -1;
  }

  // Reordenar según modeloOrden[]
  for (int i = 0; i < ordenSize; i++) {
    for (int j = 0; j < count_found; j++) {
      if (original[j].model_number == modeloOrden[i]) {
        scanDXL[i] = original[j];
        break;
      }
    }
  }

  for (int i = 0; i < ordenSize; i++) {
  Serial.printf("Slot %d -> ID: %d, Modelo: %d, Baud: %d\n",
    i, scanDXL[i].id, scanDXL[i].model_number, scanDXL[i].baudrate);
}
}
//funcion para escanear y devolver una estructura con los servos disponibles

int scanServoDxl() {
  int count_found = 0;
  
  // Limpiar arreglo previo
  for (int i = 0; i < MAX_SERVOS; i++) {
    scanDXL[i].id = 0;
    scanDXL[i].protocol = 0;
    scanDXL[i].baudrate = 0;
    scanDXL[i].model_number = 0;
  }

  for (int protocol = 1; protocol <= 2; protocol++) {
    dxl.setPortProtocolVersion((float)protocol);
    Serial.printf("Escaneando con protocolo %d\n", protocol);

    for (int i = 0; i < 13; i++) {
      uint32_t currentBaud = baud[i];
      Serial.printf("Escaneando a baud rate: %u\n", currentBaud);
      
      // Reiniciar puerto serie con el nuevo baudrate (más seguro que updateBaudRate)
      DXL_SERIAL.begin(currentBaud, SERIAL_8N1, RX_PIN, TX_PIN);
      dxl.begin(currentBaud);

      // Escaneo rápido (dependiendo de la librería)
      // Si dxl.scan() solo devuelve true/false, se debe hacer ping manualmente
      if (dxl.scan()) {
        for (int id = 1; id < 253 && count_found < MAX_SERVOS; id++) {
          if (dxl.ping(id)) {
            // Evitar duplicados
            bool already_found = false;
            for (int j = 0; j < count_found; j++) {
              if (scanDXL[j].id == id) {
                already_found = true;
                break;
              }
            }
            if (!already_found) {
              scanDXL[count_found].id = id;
              scanDXL[count_found].protocol = protocol;
              scanDXL[count_found].baudrate = currentBaud;
              scanDXL[count_found].model_number = dxl.getModelNumber(id);
              count_found++;
              Serial.printf("Dynamixel encontrado - ID: %d, Protocolo: %d, Baudrate: %u, Modelo: %d\n",
                            id, protocol, currentBaud, scanDXL[count_found - 1].model_number);
            }
          }
        }
      }
    }
  }
  return count_found;
}


void SCANFlag(){
  scanMode=true;
}
  
   
//funcion para mover individualmente un servo
void moveDxl(int index, String type, int valuePos, bool simple) {
 
  int prot = servos[index].protocolo;  // Asumiendo que servos[] está definido globalmente
  int id = servos[index].id;  // ID del servo


  //int currentPos = 0;

    if (actualProt != prot) {
    dxl.setPortProtocolVersion(prot);
    actualProt = prot;
    changeProt = true;
    Serial.printf("Cambiando protocolo a %.1f\n", actualProt);
  }

    //si es el MX106
    if (index == 0) { 
      //dxl.setPortProtocolVersion(1.0f);
      dxl.ping(servos[index].id);
      // Configuración adicional si se encuentra un Dynamixel
      /*
      dxl.torqueOff(servos[index].id);
      dxl.setOperatingMode(servos[index].id, OP_POSITION);
      dxl.torqueOn(servos[index].id);
      */
      
      if (type == "unit") {
        dxl.setGoalPosition(id, valuePos); // Posición en formato raw
        
        
      } else if (type == "angle") {
        dxl.setGoalPosition(id, valuePos, UNIT_DEGREE); // Posición en grados
      }
    /*
    idServoMovimiento = servos[index].id;
    posObjetivo = valuePos;
    */
    }
  //
    if (index == 1 ||index==2) {
     // dxl.setPortProtocolVersion(2.0f);
      dxl.ping(servos[index].id);
      // Configuración adicional si se encuentra un Dynamixel
      /*
      dxl.torqueOff(servos[index].id);
      dxl.setOperatingMode(servos[index].id, OP_POSITION);
      dxl.torqueOn(servos[index].id);
      */
      if (type == "unit") {
        dxl.setGoalPosition(id, valuePos); // Posición en formato raw
      } else if (type == "angle") {
        dxl.setGoalPosition(id, valuePos, UNIT_DEGREE); // Posición en grados
      }
    }

  //si es el AX18
    if (index == 3) {  
    /*
      //dxl.setPortProtocolVersion(1.0f);
    //==============================configuro para iniciar al AX18 ====================================// 

        if (dxl.ping(servos[index].id)) {
          Serial.println("Dynamixel AX18A encontrado y listo.");
      
          // Apagar torque
          if (!dxl.write(servos[index].id, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_OFF, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo apagar el torque");
            return;
          }
          Serial.println("Torque apagado");
      
          // Configurar límites de ángulo
          if (!dxl.write(servos[index].id, AX_CW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT) ||
              !dxl.write(servos[index].id, AX_CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CCW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo configurar el modo de operación");
            return;
          }
          Serial.println("Modo de operación configurado");
      
          // Configurar velocidad
          uint16_t speed = servos[index].V; 
          if (!dxl.write(servos[index].id,AX_MOVING_SPEED_ADDR, (uint8_t*)&speed, AX_MOVING_SPEED_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo configurar la velocidad");
            return;
          }
          Serial.println("Velocidad de movimiento configurada");
      
          // Activar torque
          if (!dxl.write(servos[index].id, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_ON, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
            Serial.println("Error: No se pudo activar el torque");
            return;
          }
          Serial.println("Torque activado");
      
        } else {
          Serial.println("Error: No se pudo encontrar el Dynamixel.");
          return;
        }
    //==============================fin de configuracion del AX18 ====================================// 
       */ 
        if (type == "unit") {     
          //dxl.write(servos[index].id, AX_GOAL_POSITION_ADDR, (uint8_t*)valuePos, AX_GOAL_POSITION_ADDR_LEN, TIMEOUT); // Posición en formato raw
          dxl.setGoalPosition(servos[index].id, valuePos);
      } else if (type == "angle") {
        int raw_position = (int)(valuePos * 1023.0 / 300.0);
        dxl.setGoalPosition(id, raw_position ); // Posición en grados convertidos
      }
      /*else if (type== "slicer"){
        int raw_position =(int)map(valuePos, 0,100,AX_CW_limit,AX_CCW_limit);
        dxl.setGoalPosition(id, raw_position ); // valor de slicer a raw 
      }
      */

      
    }


    if (simple){
      moveSimple=true;
      indexSimple=index;
      IDSimple=id;
      typeSimple=type;
      baudSimple=servos[index].baudrate;
      protSimple=servos[index].protocolo;
      posSimple=valuePos;
    }




}

//funcion para guardar el punto para una trayectoria

void addPoint(int index, String type, int valuePos) {
  if (servos[index].contadorPuntos < 10) {
    int i = servos[index].contadorPuntos;
    servos[index].puntos[i].valorPosicion = valuePos;
    servos[index].puntos[i].tipo = type;
    servos[index].contadorPuntos++;
    Serial.println("Punto agregado correctamente");
    Serial.print("contador: ");
    Serial.println(servos[index].contadorPuntos);  
  } else {
    Serial.println("Error: no se puede agregar más puntos");
  }
}

//funcion para ejecutar la secuencia
void executeSequence(){
  // 1. Obtener máximo número de puntos de cada servo
  maxPoints = 0;
  for (int i = 0; i < MAX_SERVOS; i++) {
    if (servos[i].contadorPuntos > maxPoints){
      maxPoints = servos[i].contadorPuntos;
    }

  }
  Serial.print("Punto maximo ");
  Serial.println( maxPoints);
  ejecutandoSecuencia = true;

}

void changeMoveParamet(int index,float Pvalue,float Ivalue,float Dvalue,int Vvalue,int Avalue){
  
  int prot = servos[index].protocolo;  // Asumiendo que servos[] está definido globalmente
  int id = servos[index].id;  // ID del servo

  //Guardado en la estructura de datos
  servos[index].P= Pvalue;
  servos[index].I= Ivalue;
  servos[index].D= Dvalue;
  servos[index].V= Vvalue;
  servos[index].A= Avalue;

    // Guardar en memoria NVS directamente usando prefs global
  prefs.putFloat(("P" + String(index)).c_str(), Pvalue);
  prefs.putFloat(("I" + String(index)).c_str(), Ivalue);
  prefs.putFloat(("D" + String(index)).c_str(), Dvalue);
  prefs.putInt(("V" + String(index)).c_str(), Vvalue);
  prefs.putInt(("A" + String(index)).c_str(), Avalue);

  // configuracion al servo dynamixel
  dxl.torqueOff(id);
  dxl.setOperatingMode(id, OP_POSITION);
  
  // Aplicar valores iniciales del PID y otros parámetros
  dxl.writeControlTableItem(POSITION_P_GAIN, id, Pvalue );
  dxl.writeControlTableItem(POSITION_I_GAIN, id,  Ivalue );
  dxl.writeControlTableItem(POSITION_D_GAIN, id,  Dvalue);
  dxl.writeControlTableItem(PROFILE_VELOCITY, id,  Vvalue);
  dxl.writeControlTableItem(PROFILE_ACCELERATION, id, Avalue);
  
  dxl.torqueOn(id);
  Serial.println("Servo " + String(id) + " configurado con nuevos parametros PID ,V,A");
  


  
}

//funcion con los valores para cambio de baudrate de los modelos de Dynamixel
uint8_t getBaudValue(int index, int desiredBaud) {
  switch (index) {
    case 1: // MX-106
      switch (desiredBaud) {
        case 2000000: return 0;
        case 1000000: return 1;
        case 500000:  return 3;
        case 400000:  return 4;
        case 250000:  return 7;
        case 200000:  return 9;
        case 115200:  return 16;
        case 57600:   return 34;
        case 19200:   return 103;
        case 9600:    return 207;
      }
      break;

    case 2: // XM-430
        switch (desiredBaud) {
      case 4500000: return 7;
      case 4000000: return 6;
      case 3000000: return 5;
      case 2000000: return 4;
      case 1000000: return 3;
      case 115200:  return 2;
      case 57600:   return 1;
      case 9600:    return 0;
    }
    break;
    
    case 3: // XM-430
      switch (desiredBaud) {
        case 4500000: return 7;
        case 4000000: return 6;
        case 3000000: return 5;
        case 2000000: return 4;
        case 1000000: return 3;
        case 115200:  return 2;
        case 57600:   return 1;
        case 9600:    return 0;
      }
      break;

    case 4: // AX-18A
      switch (desiredBaud) {
        case 1000000: return 1;
        case 500000:  return 3;
        //case 400000:  return 4;
        //case 250000:  return 7;
        //case 200000:  return 9;
        case 115200:  return 16;
        case 57600:   return 34;
        //case 19200:   return 103;
        case 9600:    return 207;
      }
      break;
  }

  // Valor por defecto (por ejemplo, 1M en MX y AX, 57600 en XM)
  return 1;
}


void chanceServoParamet(int index, int newBaud, int newID) {
  // Cargar baudrate real desde NVS
  int baudFromNVS = prefs.getUInt(("baud" + String(index)).c_str(), 1000000);
  Serial.printf("Usando baudrate leído de NVS: %d\n", baudFromNVS);

  // Iniciar comunicación
  DXL_SERIAL.begin(baudFromNVS, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(baudFromNVS);

  dxl.setPortProtocolVersion(servos[index].protocolo);  // ← MUY IMPORTANTE
  Serial.printf("Protocolo actual: %f\n", servos[index].protocolo);
  int id = servos[index].id;
  Serial.printf("ID actual del servo %d: %d\n", index+1, id);

  if (dxl.ping(id)) {
    Serial.println("✅  Servo detectado correctamente.");
    dxl.torqueOff(id); 
    if (newID != -1) {
      uint8_t direccionID = (index == 1 || index == 2) ? 0x07 : 0x03;
      // dxl.write(id, direccionID, (uint8_t*)&newID, 1, 100)
      if (dxl.setID(id,newID)) {
        Serial.println("✅ ID cambiado correctamente.");
        Serial.println(newID);
        servos[index].id = newID;
        prefs.putUInt(("id" + String(index)).c_str(), newID);
        dxl.torqueOn(servos[index].id); 
      } else {
        Serial.println("❌ Error al cambiar el ID.");
        dxl.torqueOn(id);
      }
    }

  if (newBaud != -1) {
    uint8_t direccionBaud =  0x04; //para MX y AX
    uint8_t baudValue = getBaudValue(index+1, newBaud);
    Serial.printf("BaudValue del servo %d: %d\n",index+1, baudValue);
    

    
    if (index == 1 || index == 2){
      if (dxl.setBaudrate(id, newBaud)) {
        Serial.println("✅ Baudrate cambiado correctamente.");
        Serial.println(newBaud);
        servos[index].baudrate = newBaud;
        prefs.putUInt(("baud" + String(index)).c_str(), newBaud);
        dxl.torqueOn(id); 

        
      } else {
        Serial.println("❌ Error al cambiar el baudrate.");
        dxl.torqueOn(id); 
    }        
    }
    else if (index==0){

      if (dxl.write(id, direccionBaud, &baudValue, 1, 1000)) {
        Serial.println("✅ Baudrate cambiado correctamente.");
        Serial.println(newBaud);
        servos[index].baudrate = newBaud;
        prefs.putUInt(("baud" + String(index)).c_str(), newBaud);
        dxl.torqueOn(id); 

        
      } else {
        Serial.println("❌ Error al cambiar el baudrate.");
        dxl.torqueOn(id); 
    }
    }

    }

  } else {
    Serial.println("❌ Servo no encontrado.");
  }
}

bool limitSwitchActivado(int servoIndex) {
  switch (servoIndex) {
    case 0: return limitTriggered[0] || limitTriggered[1];
    case 1: return limitTriggered[2];
    case 2: return limitTriggered[3] || limitTriggered[4];
    case 3: return limitTriggered[5] || limitTriggered[6];
    default: return false;
  }
}

void limitSwitchClear(int servoIndex){
  switch (servoIndex) {
    case 0:
      limitTriggered[0] = false;
      limitTriggered[1] = false;
      break;
    case 1:
      limitTriggered[2] = false;
      break;
    case 2:
      limitTriggered[3] = false;
      limitTriggered[4] = false;
      break;
    case 3:
      limitTriggered[5] = false;
      limitTriggered[6] = false;
      break;
    default:
      // No hacer nada si el índice es inválido
      break;
  }
}
