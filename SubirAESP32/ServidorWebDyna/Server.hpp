AsyncWebServer server(80);                //Instanica Server
AsyncEventSource events("/events");  //Crea repositorio de Eventos

//Manejo de WebServer Asíncrono (Handle Web Server)
void server_init(){
     //Home
     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/index.html", "text/html");});
  
     //Dirección SPIFFS
     server.serveStatic("/", SPIFFS, "/");



// Manejador del endpoint /move
server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    unsigned long startTime = millis();  // Marca el inicio
    
    //request->send(200, "text/plain", "OK");  // Enviar respuesta
    
    String servo = request->getParam("servo")->value();  // Parámetro de la solicitud
    String type  = request->getParam("type")->value();
    String value = request->getParam("value")->value();

    Serial.printf("Moviendo el  Servo %s: %s %s\n", servo.c_str(), value.c_str(), type.c_str());
    
    void moveDxl(int n, String type, int valuePos, bool simple);
    int n = servo.toInt() - 1;
    int valuePos= value.toInt();
     moveDxl(n,type,valuePos,1);

  
    // Enviar feedback por SSE (usando la función correcta con los parámetros)
    events.send(moveServoJSON(servo, type, value).c_str(), ("servo" + servo).c_str(), millis());


  
    request->send(200, "text/plain", "OK");  // Enviar respuesta

        // Marca el final y calcula la latencia
        /*
    unsigned long endTime = millis();
    unsigned long latency = endTime - startTime;

    Serial.printf("Tiempo de procesamiento /move: %lu ms\n", latency);
    */
});

 //mandar comando agregar punto al servo         
 server.on("/addPoint", HTTP_GET, [](AsyncWebServerRequest *request){
      /*
      String servo = request->getParam("servo")->value();      
      String Type  = request->getParam("Type")->value();
      String pos = request->getParam("position")->value();
*/
      String servo = request->getParam("servo") ? request->getParam("servo")->value() : "";
      String Type  = request->getParam("type") ? request->getParam("type")->value() : "";
      String pos = request->getParam("value") ? request->getParam("value")->value() : "";
      
      Serial.printf("Punto agregado al Servo %s: %s %s\n", servo.c_str(), pos.c_str(), Type.c_str());
      
      //agregar funcion de guardar punto
      void addPoint(int n, String type, int valuePos);
      int n = servo.toInt() - 1;
      int valuePos= pos.toInt();
      addPoint(n,Type,valuePos);

      events.send(addPointJSON(servo, Type, pos).c_str(), ("pointAdd" + servo).c_str(), millis());
      // Aquí podrías guardar el punto en una lista o usarlo como parte de una trayectoria
      request->send(200, "text/plain", "OK");
 });

  //mandar parametros nuevos de mov al servo         
 server.on("/moveParamet", HTTP_GET, [](AsyncWebServerRequest *request){
      String servo = request->getParam("servo")->value();
      String P  = request->getParam("p")->value();
      String I = request->getParam("i")->value();
      String D  = request->getParam("d")->value();
      String V = request->getParam("v")->value();
      String A = request->getParam("a")->value();
      
      
      Serial.printf("Parametro modificados al Servo %s: P: %s I: %s D: %s V: %s A: %s \n", servo.c_str(), P.c_str(), I.c_str(), D.c_str(), V.c_str(), A.c_str());
//agregar funcion de cambiar parametros de mov del servomotor
      void changeMoveParamet(int n,float Pvalue,float Ivalue,float Dvalue,int Vvalue,int Avalue);
      int n = servo.toInt() - 1;
      float Pvalue= P.toFloat();
      float Ivalue= I.toFloat();
      float Dvalue= D.toFloat();
      int Vvalue= V.toInt();
      int Avalue= A.toInt();


      changeMoveParamet(n,Pvalue,Ivalue,Dvalue,Vvalue,Avalue);

      events.send(changeMoveParametJSON(servo, P,I,D,V,A).c_str(), ("MoveParam" + servo).c_str(), millis());
      // Aquí podrías guardar el punto en una lista o usarlo como parte de una trayectoria
      request->send(200, "text/plain", "OK");
 });

/*
 server.on("/servoParamet", HTTP_GET, [](AsyncWebServerRequest *request){
      String servo = request->getParam("servo")->value();      
      String nuevoID  = request->getParam("-")->value();
      String nuevoBaud = request->getParam("-")->value();

     
//agregar funcion de cambiar parametros de mov del servomotor
      void chanceServoParamet(int index, int newBaud, int newID);
      int n = servo.toInt() - 1;
      int newID= nuevoID.toInt();
      int newBaud= nuevoBaud.toInt();


      chanceServoParamet(n,newBaud,newID);

      events.send(changeServoParametJSON(servo,nuevoID,nuevoBaud).c_str(), ("ServoParam" + servo).c_str(), millis());
      // Aquí podrías guardar el punto en una lista o usarlo como parte de una trayectoria
      request->send(200, "text/plain", "OK");
      
 });
*/
 server.on("/IDChance", HTTP_GET, [](AsyncWebServerRequest *request){
  String servo = request->getParam("servo")->value();      
  String nuevoID  = request->getParam("id")->value();  // Usa nombre claro
  void chanceServoParamet(int index, int newBaud, int newID);
  int n = servo.toInt() - 1;
  int newID = nuevoID.toInt();
  int newBaud = -1; // No se cambia
  String nuevoBaud=String(newBaud);

  chanceServoParamet(n, newBaud, newID);

  events.send(changeServoParametJSON(servo,nuevoID,nuevoBaud).c_str(), ("ServoParam" + servo).c_str(), millis());
  request->send(200, "text/plain", "ID actualizado");
});


server.on("/BaudChance", HTTP_GET, [](AsyncWebServerRequest *request){
  String servo = request->getParam("servo")->value();      
  String nuevoBaud  = request->getParam("baud")->value();  // Usa nombre claro
  void chanceServoParamet(int index, int newBaud, int newID);
  int n = servo.toInt() - 1;
  int newBaud = nuevoBaud.toInt();
  int newID = -1; // No se cambia
  String nuevoID= String(newID);

  chanceServoParamet(n, newBaud, newID);

  events.send(changeServoParametJSON(servo,nuevoID,nuevoBaud).c_str(), ("ServoParam" + servo).c_str(), millis());
  request->send(200, "text/plain", "Baudrate actualizado");
});

server.on("/Start", HTTP_GET, [](AsyncWebServerRequest *request){

    Serial.printf(" Ejecutando secuencia alternada...\n");

          //agregar funcion de inciiar la secuencia
   void executeSequence();
   executeSequence();
          
  
    // Enviar feedback por SSE (usando la función correcta con los parámetros)
    events.send(startSequenceJSON().c_str(), "startSeq" , millis());
  
    request->send(200, "text/plain", "OK");  // Enviar respuesta
});


server.on("/Scan", HTTP_GET, [](AsyncWebServerRequest *request){

    Serial.printf(" Escaneando Servos...\n");
    void SCANFlag();
    SCANFlag();

    request->send(200, "text/plain", "OK");  // Enviar respuesta
    


});

server.on("/EmergencyStop", HTTP_GET, [](AsyncWebServerRequest *request){

    Serial.printf(" Boton Paro presionado...\n");
    
     emergencyStop = !emergencyStop; // invierte su valor

    request->send(200, "text/plain", "OK");  // Enviar respuesta
    


});

server.on("/Home", HTTP_GET, [](AsyncWebServerRequest *request){

    Serial.printf(" Boton Home presionado...\n");
    HomeState=true;
     
    request->send(200, "text/plain", "OK");  // Enviar respuesta
    


});

server.on("/pingtest", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "pong");
});

server.on("/reportLatencia", HTTP_GET, [](AsyncWebServerRequest *request){
  if(request->hasParam("valor")){
    String val = request->getParam("valor")->value();
    Serial.print("Latencia reportada: ");
    Serial.println(val);
    // Aquí puedes guardar o usar ese valor
    request->send(200, "text/plain", "OK");
  } else {
    request->send(400, "text/plain", "Falta parámetro valor");
  }
  check=true;
});

     // → Al conectarse un cliente
     events.onConnect([](AsyncEventSourceClient *client){
     if(client->lastId()){
          Serial.println("Cliente reconectado!");
          Serial.printf("El último ID de mensaje que se recibió: %u\n", 
                    client->lastId());
          delay(250);
     }client->send("Hola!", NULL, millis(), 10000);

       for (int p = 0; p < 4; p++) {
    String evento = "chanceIcon" + String(p + 1);
    String flag = String(servoActivo[p]); 
    client->send(chanceIconJSON(String(p + 1), flag).c_str(), evento.c_str(), millis());
  }
     });
     
     server.addHandler(&events); //Carga manejo de eventos
     server.begin();             //Inicia el servidor
}
