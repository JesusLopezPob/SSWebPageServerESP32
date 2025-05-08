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
    String servo = request->getParam("servo")->value();  // Parámetro de la solicitud
    String type  = request->getParam("type")->value();
    String value = request->getParam("value")->value();

    Serial.printf("Moviendo el  Servo %s: %s %s\n", servo.c_str(), value.c_str(), type.c_str());
  
    // Enviar feedback por SSE (usando la función correcta con los parámetros)
    events.send(moveServo(servo, type, value).c_str(), ("servo" + servo).c_str(), millis());
  
    request->send(200, "text/plain", "OK");  // Enviar respuesta
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
      
      //agregar funcion de mover el servomotor

      events.send(addPoint(servo, Type, pos).c_str(), ("pointAdd" + servo).c_str(), millis());
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
//agregar funcion de mover el servomotor

      events.send(changeMoveParamet(servo, P,I,D,V,A).c_str(), ("MoveParam" + servo).c_str(), millis());
      // Aquí podrías guardar el punto en una lista o usarlo como parte de una trayectoria
      request->send(200, "text/plain", "OK");
 });
        


     // → Al conectarse un cliente
     events.onConnect([](AsyncEventSourceClient *client){
     if(client->lastId()){
          Serial.println("Cliente reconectado!");
          Serial.printf("El último ID de mensaje que se recibió: %u\n", 
                    client->lastId());
          delay(250);
     }client->send("Hola!", NULL, millis(), 10000);
     });
     
     server.addHandler(&events); //Carga manejo de eventos
     server.begin();             //Inicia el servidor
}
