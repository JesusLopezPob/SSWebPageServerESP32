//configuracion para la esp32 como AP

  // Configura el ESP32 como punto de acceso

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
