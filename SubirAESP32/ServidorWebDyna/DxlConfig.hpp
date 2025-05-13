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


  //config paar AX18

  uint8_t id_Ax18 = servos[3].id;

   dxl.setPortProtocolVersion(id_Ax18);
   if (dxl.ping(id_Ax18)) {  
    Serial.println("Servo 3 encontrado (Protocolo 1.0).");
    // Apagar torque para configurar
    if (dxl.write(id_Ax18, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_OFF, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
      Serial.println("Servo 3: Torque apagado.");
    } else {
      Serial.println("Error: No se pudo apagar el torque del servo 3.");
    }
    
    // Configurar límites de ángulo
    if (dxl.write(id_Ax18, AX_CW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT) &&
        dxl.write(id_Ax18, AX_CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&AX_CCW_limit, AX_ANGLE_LIMIT_ADDR_LEN, TIMEOUT)) {
      Serial.println("Servo 3: Límites de ángulo configurados.");
    } else {
      Serial.println("Error: No se pudieron configurar los límites de ángulo del servo 3.");
    }
    // Configurar velocidad de movimiento
    if (dxl.write(id_Ax18, AX_MOVING_SPEED_ADDR, (uint8_t*)&servos[3].V, AX_MOVING_SPEED_ADDR_LEN, TIMEOUT)) {
      Serial.println("Servo 3: Velocidad configurada.");
    } else {
      Serial.println("Error: No se pudo configurar la velocidad del servo 3.");
    }
    // Activar torque
    if (dxl.write(id_Ax18, AX_TORQUE_ENABLE_ADDR, (uint8_t*)&TURN_ON, AX_TORQUE_ENABLE_ADDR_LEN, TIMEOUT)) {
      Serial.println("Servo 3: Torque activado.");
    } else {
      Serial.println("Error: No se pudo activar el torque del servo 3.");
    }
    
  } else {
    Serial.println("Error: No se encontró el servo 3.");
    while (true);  // Detiene el programa si no se encuentra el servo
  }

  // Regresar a protocolo 2.0 para servos 1 y 2
  dxl.setPortProtocolVersion(2.0);

  

}


//funcion para escanear y devolver una estructura con los servos disponibles


//funcion para mover individualmente un servo



//funcion para ejecutar la secuencia


//funcion para guardar el punto para una trayectoria
