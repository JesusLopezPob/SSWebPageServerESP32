//Libreria de las funciones para  configuracion y control Dynamixel con ESP32
//derechos reservados ----

//funcion para configurar a los servos Dynamixel para un inicio
void configDXL(){
  
  // Inicializa el puerto serial para Dynamixel
  DXL_SERIAL.begin(DXL_Baud, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(DXL_Baud);


    
    for (int i = 0; i < 4; i++) {
        // Definir los ID
        servos[i].id = (i == 0) ? 4 : i; //  { 4, 1, 2, 3}

        // Definir los baudrate
        servos[i].baudrate = 1000000;

        //definir los protocolos
        servos[i].protocolo=(i < 3) ? 2.0 : 1.0; // { 2.0, 2.0, 2.0 , 1.0}

        // Definir protocolos (protocolo ya está inicializado en el constructor)

        // Definir PID
        servos[i].P = (i < 3) ? 120 : -1;   //{ 120, 120, 120 , -1}
        servos[i].I = (i < 3) ? 15 : -1;    // { 15, 15, 15 , -1}
        servos[i].D = (i < 3) ? 1 : -1;     // { 1, 1, 1 , -1}

        // Definir V y A
        servos[i].V = (i < 3) ? 100 : 50;   // { 100, 100, 100 , 50}
        servos[i].A = (i < 3) ? 50 : -1;    // { 50, 50, 50, -1}

        servos[i].contadorPuntos = 0;

        for (int j = 0; j < 10; j++) {
            servos[i].puntos[j].valorPosicion = 0;
            servos[i].puntos[j].tipo.clear();
        }
    }
    
  
  
  //config para MX106


  //config para XM
  for  (int i=1; i<=2;i++){
    uint8_t id = servos[i].id;
    dxl.ping(id);
    dxl.torqueOff(id);
    dxl.setOperatingMode(id, OP_POSITION);
    
    // Aplicar valores iniciales del PID y otros parámetros
    dxl.writeControlTableItem(POSITION_P_GAIN, id, servos[i].P);
    dxl.writeControlTableItem(POSITION_I_GAIN, id, servos[i].I);
    dxl.writeControlTableItem(POSITION_D_GAIN, id, servos[i].D);
    dxl.writeControlTableItem(PROFILE_VELOCITY, id, servos[i].V);
    dxl.writeControlTableItem(PROFILE_ACCELERATION, id, servos[i].A);

    dxl.torqueOn(id);
    Serial.println("Servo " + String(id) + " configurado en posición (Protocolo 2.0).");
    
  }

//==============================configuro para iniciar al AX18 ====================================// 

   dxl.setPortProtocolVersion(1.0f);
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
      Serial.println("Error: No se pudo encontrar el Dynamixel.");
      return;
    }
//==============================fin de configuracion del AX18 ====================================// 

  // Regresar a protocolo 2.0 para servos 1 y 2
  dxl.setPortProtocolVersion(2.0f);


  

}


//funcion para escanear y devolver una estructura con los servos disponibles

int scanServoDxl() {
  int baud[13] = {9600,19200, 57600, 115200, 200000,250000, 400000,500000, 1000000, 2000000, 3000000,4000000, 4500000};
  int count_found = 0;
  int found = 0;

  for (int protocol = 1; protocol <= 2; protocol++) {
    dxl.setPortProtocolVersion((float)protocol);
    Serial.print("Escaneando con protocolo ");
    Serial.println(protocol);

    for (int i = 0; i < 13; i++) {
      Serial.print("Escaneando a baud rate: ");
      Serial.println(baud[i]);
      DXL_SERIAL.updateBaudRate(baud[i]);
      dxl.begin(baud[i]);
      found = dxl.scan();
      if (found) {
        for (int id = 1; id < 253; id++) {
          if (dxl.ping(id)) {
            // Verificar si ya está registrado
            bool already_found = false;
            for (int j = 0; j < count_found; j++) {
              if ( scanDXL[j].id == id) {
                already_found = true;
                break;
              }
            }
            if (!already_found && count_found < MAX_SERVOS) {
              scanDXL[count_found].id = id;
              scanDXL[count_found].protocol = protocol;
              scanDXL[count_found].baudrate = baud[i];
              int Model_number=dxl.getModelNumber(id);
              scanDXL[count_found].model_number= Model_number;
              count_found++;
              Serial.print("Dynamixel encontrado - ID: ");
              Serial.print(id);
              Serial.print(", Protocolo: ");
              Serial.print(protocol);
              Serial.print(", Baudrate: ");
              Serial.print(baud[i]);
              Serial.print(", Modelo: ");
              Serial.println(Model_number);
            }
          }
        }
      }
    }
  }
  return count_found;
}

  
    

//funcion para mover individualmente un servo
void moveDxl(int index, String type, int valuePos) {
 
  int prot = servos[index].protocolo;  // Asumiendo que servos[] está definido globalmente
  int id = servos[index].id;  // ID del servo

//si utiliza el protocolo 2.0
  if (prot == 2) {
    dxl.setPortProtocolVersion(2.0f);
    dxl.ping(servos[index].id);
    // Configuración adicional si se encuentra un Dynamixel
    dxl.torqueOff(servos[index].id);
    dxl.setOperatingMode(servos[index].id, OP_POSITION);
    dxl.torqueOn(servos[index].id);
    
    if (type == "unit") {
      dxl.setGoalPosition(id, valuePos); // Posición en formato raw
    } else if (type == "angle") {
      dxl.setGoalPosition(id, valuePos, UNIT_DEGREE); // Posición en grados
    }
  }

  //si es el AX18
  if (index == 3) {  
  
    dxl.setPortProtocolVersion(1.0f);
//==============================configuro para iniciar al AX18 ====================================// 

   dxl.setPortProtocolVersion(1.0f);
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
  
      if (type == "unit") {     
        //dxl.write(servos[index].id, AX_GOAL_POSITION_ADDR, (uint8_t*)valuePos, AX_GOAL_POSITION_ADDR_LEN, TIMEOUT); // Posición en formato raw
        dxl.setGoalPosition(servos[index].id, valuePos);
    } else if (type == "angle") {
      int raw_position = (int)(valuePos * 1023.0 / 300.0);
      dxl.setGoalPosition(id, raw_position ); // Posición en grados convertidos
    }

    
  }
  
  



}



//funcion para ejecutar la secuencia



//funcion para guardar el punto para una trayectoria

void addPoint(int index, String type, int valuePos) {
  if (servos[index].contadorPuntos < 10) {
    int i = servos[index].contadorPuntos;
    servos[index].puntos[i].valorPosicion = valuePos;
    servos[index].puntos[i].tipo = type;
    servos[index].contadorPuntos++;
    Serial.println("Punto agregado correctamente");
  } else {
    Serial.println("Error: no se puede agregar más puntos");
  }
}
