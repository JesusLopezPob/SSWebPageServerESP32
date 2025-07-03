
# Manual del Desarrollador

Este manual está diseñado para guiar a desarrolladores en la comprensión, modificación y expansión del sistema de control remoto embebido basado en ESP32. La arquitectura modular del proyecto permite la incorporación de nuevas funciones y dispositivos con mínima intervención en el núcleo existente.

---
###  1. ¿Cómo extender o modificar el código?

#### A. Agregar una nueva pestaña (por ejemplo, un nuevo servo o módulo)

1. **Abrir `index.html`**
2. Copiar y pegar una pestaña existente:
   ```html
   <div class="tab" onclick="openTab(event, 'pestanaX')">
     Servo X <img id="estado-servoX" class="icono-servo" src="iconoNO.png" alt="estado">
   </div>
   ```
3. Crear el contenido de la pestaña:
   ```html
   <div id='pestanaX' class='tab-content'>
     <!-- contenido -->
   </div>
   ```
4. Subir los cambios al ESP32 usando SPIFFS.
---
####  B. Añadir nuevos eventos en `script.js`
1. Localiza la sección de `EventSource`.
2. Agrega una nueva escucha:
   ```js
   source.addEventListener('nuevoEvento', function(e) {
     const data = JSON.parse(e.data);
     console.log("Nuevo evento:", data);
   }, false);
   ```
---
####  C. Crear nuevas rutas HTTP en el firmware
1. Abre `server.hpp` .
2. Agrega una nueva ruta:
   ```cpp
   server.on("/nuevaRuta", HTTP_GET, [](AsyncWebServerRequest *request){
     //aqui poner tu logica
     request->send(200, "text/plain", "OK");
   });
   ```
3. (Opcional) Lanza un evento:
   ```cpp
   //aqui poner tu logica
   events.send("mensaje", "nuevoEvento");
   ```
---
#### D. Subir archivos a SPIFFS

1. Coloca los archivos en la carpeta `/data`.
2. En Arduino IDE: `Herramientas > ESP32 Sketch Data Upload`.
3. Verifica desde el Monitor Serial que la carga fue exitosa.
---
### 2. Variables o funciones críticas

| Función                     | Descripción                                                  | Archivo     |
|----------------------------|--------------------------------------------------------------|-------------|
| `openTab()`                | Cambia pestañas e imagen dinámica                           | script.js   |
| `submitForm(servo)`        | Envía posición a un servo                                    | script.js   |
| `addPoint(servo)`          | Agrega un punto de trayectoria                               | script.js   |
| `submitMoveParame(servo)`  | Cambia parámetros PID, velocidad y aceleración              | script.js   |
| `guardarID(servo)`         | Guarda nuevo ID para el servo                               | script.js   |
| `guardarBaud(servo)`       | Configura el baudrate del servo                             | script.js   |
| `executeSequence()`        | Ejecuta la secuencia alternada                              | script.js   |
| `actualizarEstadoServo()`  | Actualiza íconos de conexión                                 | script.js   |
| `source.addEventListener`  | Escucha eventos del ESP32                                    | script.js   |
---
### 3. ¿Cómo agregar un nuevo sensor o actuador?

#### A. Conexión física al ESP32

- Identifica si es señal **digital** o **analógica**.
- Conecta el sensor y declara su pin la seccion de  `variables.h`:
  ```cpp
  // =========================
    //Sensores y Finales de carrera
    // =========================
    ....
    const int sensorPin = 34;

  ```
- Toma en cuenta que existe un array de sensores de final de carrera y de fuerza en la seccion de **Sensores y Finales de carrera** del archivo  `variables.h`:
  ```cpp
  // =========================
    //Sensores y Finales de carrera
    // =========================
    int Finalswitch[]={32,33,25,26,13,14,27};

    int ForceSensors[]={34,35}; 
  ```
- No es posible utilizar el ADC2 (pines 25, 26, 27, 14, 12, 13, 15, 2 y 4) mientras esté activo el módulo Wi-Fi del ESP32, ya que comparten el mismo controlador y entran en conflicto.
- El GPIO 12 debe dejarse libre o en nivel bajo durante el arranque, ya que determina el voltaje del regulador interno; si se encuentra en nivel alto al encender, el ESP32 puede seleccionar 1.8 V en lugar de 3.3 V, lo que puede provocar fallos de arranque o incluso dañar componentes externos. Por ello, se recomienda no usar este pin o asegurarse de que permanezca en bajo durante el encendido.
#### B. Leer desde el firmware
```cpp
int sensorValue = analogRead(sensorPin);
if(sensorValue > UMBRAL){
  events.send("{\"sensor\":\"distancia\",\"valor\":" + String(sensorValue) + "}", "sensorEvento");
}
```
#### C. Escuchar en `script.js`
```js
source.addEventListener('sensorEvento', function(e) {
  const data = JSON.parse(e.data);
  document.getElementById("sensor-status").innerText = `Valor: ${data.valor}`;
});
```
#### D. Mostrar en `index.html`

```html
<div id="sensor-status">Esperando señal...</div>
```
---
### Recomendaciones 
- Comenta todo código nuevo.
- Usa nombres descriptivos para eventos y variables.
- Asegúrate de reiniciar el ESP32 después de subir nuevos archivos.
- Mantén las funciones encapsuladas y separadas por propósito.
- Documenta cada nuevo endpoint o evento para futuras referencias.
---

## Carga SPIFFS (Sistema de Archivos del ESP32)

La interfaz web de este proyecto no depende de servidores externos, sino que se **almacena directamente en la memoria flash del ESP32** mediante el sistema de archivos SPIFFS (*Serial Peripheral Interface Flash File System*). Esto permite que el ESP32 sirva archivos estáticos (como HTML, CSS, JS e imágenes) de forma autónoma a través del navegador web de cualquier dispositivo conectado a su red.

A continuación se detalla el proceso completo para preparar, configurar y subir correctamente los archivos al ESP32 utilizando SPIFFS.

---

### 1. Instalar el plugin **ESP32 Sketch Data Upload**

El IDE de Arduino no incluye de forma predeterminada la funcionalidad para cargar carpetas de archivos al sistema SPIFFS del ESP32. Para ello, es necesario instalar un plugin adicional llamado **ESP32FS Tool**.

#### Pasos para instalar el plugin:

1. Cierra el IDE de Arduino (si está abierto).
2. Descarga el plugin desde el repositorio oficial:  
 [ESP32 Sketch Data Upload – GitHub](https://github.com/me-no-dev/arduino-esp32fs-plugin)
3. Descomprime el archivo `.zip` descargado.
4. Copia la carpeta descomprimida `ESP32FS` en el siguiente directorio, según tu sistema operativo:

| Sistema Operativo | Ruta donde pegar el plugin                                         |
|-------------------|---------------------------------------------------------------------|
| **Windows**       | `C:\Users\<tu_usuario>\Documents\Arduino\tools\ESP32FS\tool\`       |
| **macOS**         | `~/Documents/Arduino/tools/ESP32FS/tool/`                          |
| **Linux**         | `~/Arduino/tools/ESP32FS/tool/`                                     |

5. Asegúrate de que la ruta final contenga un archivo llamado `esp32fs.jar`.

6. Vuelve a abrir el Arduino IDE. Debería aparecer una nueva opción en el menú:
   ```
   Herramientas > ESP32 Sketch Data Upload
   ```

**Verifica que esté visible** antes de continuar con los pasos siguientes.
---
### 2. Crear la carpeta `/data`

El sistema SPIFFS carga únicamente los archivos que se encuentren dentro de una carpeta llamada exactamente `/data`, ubicada al mismo nivel del archivo `.ino` principal de tu proyecto.

#### Estructura recomendada:

```bash
TuProyecto/
├── TuProyecto.ino
└── data/
    ├── index.html
    ├── styles.css
    ├── script.js
    ├── normalize.css
    ├── fondo.png
    ├── iconoSI.png
    ├── iconoNO.png
    ├── servo1.jpeg
    ├── servo2.jpeg
    ├── servo3.jpeg
    ├── servo4.jpeg
    └── confi.jpeg
```

 **Importante:**
- El nombre de la carpeta debe ser exactamente `data` (todo en minúsculas).
- Todos los archivos que se usarán en el navegador (como HTML, CSS, JS e imágenes) deben estar dentro de esta carpeta.

---

###  3. Subir los archivos al ESP32

Una vez que tienes la carpeta `/data` lista, puedes subir su contenido a la memoria flash del ESP32.

#### Procedimiento:

1. Abre el **proyecto en el Arduino IDE**.
2. Asegúrate de seleccionar la **placa correcta** desde el menú:
   ```
   Herramientas > Placa > ESP32 Dev Module
   ```
3. Selecciona el **puerto correcto** donde está conectado tu ESP32:
   ```
   Herramientas > Puerto > COMX o /dev/ttyUSBX
   ```
4. Conecta tu ESP32 a la computadora mediante USB.

5. Ahora, haz clic en el menú:
   ```
   Herramientas > ESP32 Sketch Data Upload
   ```
6. Espera unos segundos mientras se carga el sistema de archivos. Verás en el monitor de salida mensajes similares a:
```
[SPIFFS] Uploading file: /index.html
[SPIFFS] Uploading file: /styles.css
...
[SPIFFS] Total file size: 78.2 KB
[SPIFFS] Success!
```
---

###  4. Verificación en Monitor Serial

Para confirmar que los archivos fueron cargados correctamente:

1. Abre el **Monitor Serial** (Ctrl+Shift+M).
2. Asegúrate de que tu código incluya la inicialización del SPIFFS, por ejemplo:

```cpp
if (!SPIFFS.begin(true)) {
  Serial.println("Error al montar SPIFFS");
  return;
}
Serial.println("SPIFFS montado correctamente");
```

3. Si el sistema se montó con éxito, deberías ver un mensaje como:
```
SPIFFS montado correctamente
```

Además, cuando accedas a la dirección IP del ESP32 en el navegador, podrás ver la interfaz web que tú diseñaste.

---
### Errores comunes y cómo resolverlos

| Error                                           | Posible causa / solución                                                  |
|------------------------------------------------|---------------------------------------------------------------------------|
| `SPIFFS mount failed`                          | El archivo `.ino` no contiene `SPIFFS.begin()` o está mal implementado.  |
| Plugin no aparece en el menú                   | Plugin mal instalado. Verifica ruta y reinicia Arduino IDE.              |
| Archivos no se actualizan                      | Asegúrate de guardar todos los cambios antes de hacer el upload.         |
| Carga fallida, aparece "No serial port found"  | Verifica el cable USB y el puerto seleccionado en el IDE.                |

---

###  Recomendaciónes

Incluye un bloque como este en tu `setup()` para confirmar los archivos disponibles:

```cpp
File root = SPIFFS.open("/");
File file = root.openNextFile();
while (file) {
  Serial.print("Archivo encontrado: ");
  Serial.println(file.name());
  file = root.openNextFile();
}
```

Esto te ayudará a verificar desde el Monitor Serial qué archivos están presentes y disponibles para ser servidos por el ESP32, con estos pasos completados, la ESP32 estará sirviendo una página web completamente funcional desde su propia memoria, sin depender de servidores externos o internet.

 ##  Compilación Arduino IDE

El firmware es la parte del proyecto que corre directamente sobre el microcontrolador ESP32. Este código es responsable de crear el servidor web, controlar los servomotores Dynamixel, gestionar los archivos almacenados en SPIFFS y comunicarse con la interfaz del usuario.

Para compilar y cargar correctamente el firmware en el ESP32 desde el **Arduino IDE**, es fundamental seguir cuidadosamente los pasos descritos a continuación.

---
### 1. Seleccionar placa y puerto

Antes de compilar, debes asegurarte de que el entorno de desarrollo esté configurado correctamente para el ESP32:

#### A. Seleccionar la placa correcta

1. Abre Arduino IDE.
2. Ve al menú superior:
   ```
   Herramientas > Placa > ESP32 Arduino > ESP32 Dev Module
   ```
3. Si no aparece “ESP32 Dev Module”, debes instalar el soporte para ESP32:
   - Ir a `Archivo > Preferencias`
   - En "Gestor de URLs Adicionales de Tarjetas" añade:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Luego ve a:
     ```
     Herramientas > Placa > Gestor de placas...
     ```
   - Busca **esp32** e instala el paquete oficial de **Espressif Systems**.

#### B. Seleccionar el puerto adecuado

1. Conecta tu ESP32 por USB a la computadora.
2. Luego en Arduino IDE ve a:
   ```
   Herramientas > Puerto > COMx (Windows) o /dev/ttyUSBx (Linux/macOS)
   ```

> Asegúrate de que **el puerto cambie** al conectar y desconectar el ESP32. Si no aparece, puede deberse a un problema de drivers.

---

### 2. Cargar librerías necesarias

El proyecto utiliza varias librerías externas y del núcleo de ESP32. Asegúrate de tenerlas instaladas para evitar errores de compilación.

#### A. Librerías externas necesarias

Instálalas desde:  
`Programa > Incluir Librería > Administrar Bibliotecas`

| Librería                | Versión recomendada | Función principal                                    |
|------------------------|---------------------|------------------------------------------------------|
| **Dynamixel2Arduino**  | ≥ 0.3.0             | Control de servomotores Dynamixel vía UART          |
| **ESPAsyncWebServer**  | 1.2.4               | Servidor web asíncrono para ESP32                   |
| **Arduino_JSON**       | ≥ 0.2.0             | Procesamiento y análisis de objetos JSON            |

 Algunas librerías requieren otras dependencias como `AsyncTCP` (instálala también si se solicita).

---

###  3. Configuración del archivo principal (.ino)

Asegúrate de que tu archivo `.ino` contenga al menos lo siguiente en su función `setup()`:

```cpp

void setup() {
  //iniciar Serial
  Serial.begin(115200);

   //inciar WIFI
  wifi_AP_init(ssid,pass);
  //connectToWiFi();
  delay(1000);

  // Acceder al SPIFFS
  spiffs_init();
   //configurar los servomotores
  InitconfigDXL();
  delay(100);
  //debugging de servos activos
  Serial.println("Configuracion completa."); 
   for (int p = 0; p < 4; p++) {
    Serial.println(servoActivo[p]);
 }
  //incializar el Server
  server_init();
 }
```
Para agregar nuevos estados para la FSM debe ponerlo entre el bloque siguiente:
```cpp

void loop() {
 if (!puntoEnEjecucion) {
    .....
 }
 if (moveSimple) {
    .....
 }
 if (scanMode){
    .....
 }

//inserte nuevos estados aqui

/*
//medicion de latencia
unsigned long t_actual = millis();
if (t_actual -  t_anterior >= t_sensado) {
    ......
}
*/


}


```
**Nota**: La sección de medición de latencia debe permanecer comentada, a menos que sea necesario realizar pruebas específicas sobre el rendimiento. De lo contrario, mantenerla activa puede generar inestabilidad al recibir comandos, afectando la comunicación del sistema.

> Puedes dividir la lógica en archivos auxiliares como `server.hpp`, `DXLConfig.hpp`, etc. siguiendo una arquitectura modular.

---

###  4. Subir el firmware al ESP32

Una vez que todo esté configurado:

1. Guarda todos los archivos del proyecto.
2. Haz clic en el botón `Subir` (ícono con flecha hacia la derecha).
3. Espera a que compile y se cargue el firmware al ESP32.
4. Abre el `Monitor Serial`:
   ```
   Herramientas > Monitor Serial
   ```
   - Configura la velocidad a `115200 baudios`.

Deberías ver en la consola mensajes como:

```
Dirección IP: 192.168.4.1
Cargando Sistema de Archivos SPIFFS Cargado con éxito
Servo con ID 4 d.....
.....
.....
.....
Configuracion completa.
```

---

### Posibles errores y cómo solucionarlos

| Error en consola                       | Causa probable                                       | Solución sugerida                                         |
|----------------------------------------|------------------------------------------------------|-----------------------------------------------------------|
| `SPIFFS mount failed`                  | No se inicializó correctamente `SPIFFS.begin()`      | Verifica código y asegúrate de que `SPIFFS.begin(true)` esté presente |
| `No such file or directory`            | Librería faltante                                    | Instala la librería desde el Gestor de Bibliotecas        |
| `Failed to connect to ESP32`           | Puerto incorrecto o mal contacto                     | Revisa cable USB, reinicia ESP32, cambia puerto           |
| `Guru Meditation Error` (core dump)    | Error crítico en tiempo de ejecución                 | Verifica punteros, delays, accesos inválidos              |

---

### Recomendaciones 

- Usa nombres claros para funciones y variables, especialmente si vas a trabajar con múltiples servos.
- Comenta tu código, especialmente en funciones como `submitForm()`, `addPoint()`, `startSequence()`, etc.
- Si vas a trabajar con múltiples configuraciones, guarda perfiles diferentes en el IDE o usa PlatformIO.
- Siempre revisa la salida del Monitor Serial tras cada carga. Es tu mejor herramienta de depuración.

---
 