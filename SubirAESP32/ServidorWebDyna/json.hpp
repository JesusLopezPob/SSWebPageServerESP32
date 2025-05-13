//Instancias 
JSONVar JDoc;                             //Variable de almacenamiento Json

// Función general para generar un JSON para movero al servo
String moveServo(String servo, String type, String value) {
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
String addPoint(String servo, String Type, String value) {
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
String changeMoveParamet(String servo, String P, String I,String D, String V, String A ){        
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

String startSequence(){        
    JDoc = JSONVar();  // Limpiar el contenido de JDoc 
        // Asignación de los valores a los campos JSON
    JDoc["start"] = "1";

     // Convertir el JSON a string
    String jsonString = JSON.stringify(JDoc);
    Serial.println("→ " + jsonString);  // Imprimir JSON en consola
    return jsonString;  // Retornar el string JSON    
}
