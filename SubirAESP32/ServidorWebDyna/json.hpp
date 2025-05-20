//Instancias 
JSONVar JDoc;                             //Variable de almacenamiento Json

// Función general para generar un JSON para movero al servo
String moveServoJSON(String servo, String type, String value) {
    JDoc = JSONVar();  // Limpiar el contenido de JDoc

    // Asignación de los valores a los campos JSON
    JDoc["servo"] = servo;
    JDoc["type"] = type;
    JDoc["value"] = value;

    // Convertir el JSON a string
    String jsonString = JSON.stringify(JDoc);
    Serial.println("→ " + jsonString);  // Imprimir JSON en consola
    return jsonString;  // Retornar el string JSON
}

// Función general para generar un JSON para mover o agregar un punto al servo
String addPointJSON(String servo, String Type, String value) {
    JDoc = JSONVar();  // Limpiar el contenido de JDoc

    // Asignación de los valores a los campos JSON
    JDoc["servo"] = servo;
    JDoc["Type"] = Type;
    JDoc["value"] = value;

    // Convertir el JSON a string
    String jsonString2 = JSON.stringify(JDoc);
    Serial.println("→ " + jsonString2);  // Imprimir JSON en consola
    return jsonString2;  // Retornar el string JSON
}
//para mandar los nuevos parametros de movimiento PID, Vel y Acel
String changeMoveParametJSON(String servo, String P, String I,String D, String V, String A ){        
    JDoc = JSONVar();  // Limpiar el contenido de JDoc 
        // Asignación de los valores a los campos JSON
    JDoc["servo"] = servo;
    JDoc["P"] = P;
    JDoc["I"] = I;
    JDoc["D"] = D;
    JDoc["V"] = V;
    JDoc["A"] = A;

     // Convertir el JSON a string
    String jsonString = JSON.stringify(JDoc);
    Serial.println("→ " + jsonString);  // Imprimir JSON en consola
    return jsonString;  // Retornar el string JSON    
}

String startSequenceJSON(){        
    JDoc = JSONVar();  // Limpiar el contenido de JDoc 
        // Asignación de los valores a los campos JSON
    JDoc["start"] = "1";

     // Convertir el JSON a string
    String jsonString = JSON.stringify(JDoc);
    Serial.println("→ " + jsonString);  // Imprimir JSON en consola
    return jsonString;  // Retornar el string JSON    
}

String scanResultsJSON(ServoInfo servos[], int count) {
  JSONVar JArray;  // Inicializar objeto JSON

  for (int i = 0; i < count; i++) {
    JSONVar JDoc;
    JDoc["id"] = servos[i].id;
    JDoc["protocol"] = servos[i].protocol;
    JDoc["baudrate"] = servos[i].baudrate;
    JDoc["model_number"] = servos[i].model_number;
    JArray[i] = JDoc;  // Agregar objeto al array
  }

  String jsonString = JSON.stringify(JArray);
  Serial.println("Todos los servos: " + jsonString);
  return jsonString;
}
