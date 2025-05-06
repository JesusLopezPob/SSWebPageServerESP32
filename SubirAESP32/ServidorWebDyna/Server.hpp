AsyncWebServer server(80);                //Instanica Server
AsyncEventSource events("/events");  //Crea repositorio de Eventos

//Manejo de WebServer Asíncrono (Handle Web Server)
void server_init(){
     //Home
     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/index.html", "text/html");});
  
     //Dirección SPIFFS
     server.serveStatic("/", SPIFFS, "/");

     //Presionar un botón
     server.on("/nuevo", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(200, "text/plain", "OK");
          events.send(crearJson().c_str(),"perro_salchicha",millis());
     });
     
     //Presionar un botón
     server.on("/bot1", HTTP_GET, [](AsyncWebServerRequest *request){
          led_sta = !led_sta; request->send(200, "text/plain", "OK");
          Serial.println("← Botón presionado, nuevo estado = " + 
                    String(led_sta));
     });
     



     //mandar comando mover instantaneo del servo
     server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
          String servo = request->getParam("servo")->value();
          String type  = request->getParam("type")->value();
          String value = request->getParam("value")->value();
          
          // Aquí puedes usar esas variables para mover el servo correspondiente
          
          // Enviar feedback por SSE
          JSONVar j;
          j["servo"] = servo;
          j["type"] = type;
          j["value"] = value;
          events.send(JSON.stringify(j).c_str(), "servo" + servo, millis());
          
          request->send(200, "text/plain", "OK");
          });


      //mandar comando agregar punto al servo         
     server.on("/addpoint", HTTP_GET, [](AsyncWebServerRequest *request){
          String servo = request->getParam("servo")->value();
          String type  = request->getParam("type")->value();
          String value = request->getParam("value")->value();
          
          Serial.printf("Punto agregado al Servo %s: %s %s\n", servo.c_str(), value.c_str(), type.c_str());
          
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
