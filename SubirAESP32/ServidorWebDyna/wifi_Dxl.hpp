//configuracion para la esp32 como AP
void wifi_AP_init(const char* ssid, const char* pass) {
  for (int attempt = 0; attempt < 5; attempt++) {
    WiFi.softAP(ssid, pass);  // Configura el ESP32 como punto de acceso
    delay(1000);  // Espera 1 segundo para que el AP se configure

    IPAddress IP = WiFi.softAPIP();  // Obtener la IP del AP
    if (IP != IPAddress(0, 0, 0, 0)) {
      Serial.print("Dirección IP: ");
      Serial.println(IP);
      return;  // Exit the function if the AP was successfully configured
    }

    Serial.println("Error al configurar el AP. Intentando nuevamente...");
  }
  
  Serial.println("No se pudo configurar el AP después de 5 intentos.");
}

//configuracion para la esp32 a una conexion externa
void connectToWiFi() {

  const char* SSId = "JESUSLAP7276";      
  const char* password = "41#3Mf83";    
  
  Serial.println("Conectando a WiFi...");
  WiFi.begin(SSId, password);

  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 10000; // 10 segundos de tiempo de espera

  // Esperar hasta que se conecte o se agote el tiempo
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado exitosamente.");
    Serial.print("IP asignada: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ No se pudo conectar al WiFi.");
  }
}
