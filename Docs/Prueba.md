# 📚 Documentación del Proyecto  

**Nombre del Proyecto**: Servidor Web ESP32  
**Descripción**: Sistema de control remoto para brazo robotico basado en servidor web embebido en una ESP32 

---
**Índice rápido**  
- [🚀 Instalación](#🚀-instalación)  
- [📋 Procedimiento inicialización](#📋-procedimiento-inicialización)  
  - [1. Alimentación del circuito](#1-alimentación-del-circuito-y-shield-dxl)  
  - [2. Conexión de servomotores](#2-conexión-de-servomotores-dynamixel)  
  - [3. 📶 Conexión vía Wi-Fi al dispositivo ESP32-AP](#3-conexión-vía-wi-fi-al-dispositivo-esp32-ap)
  - [4. 🌐 Acceso a la interfaz web](#4-acceso-a-la-interfaz-web-del-ESP32)
- [Estructura del Código](#-estructura-del-código)
- [Diagrama de Estados](#-diagrama-de-estados)
- [Manual del Desarrollador](#-manual-del-desarrollador)
- [Carga SPIFFS](#-carga-spiffs)
- [Compilación Arduino](#-compilación-arduino)
- [Pendientes](#-pendientes)
---

## 🚀 Instalación  
```bash
# Comandos para instalar (ejemplo)
git clone https://github.com/tu-usuario/tu-repo.git
cd tu-repo
npm install  # o pip install, etc.

```
## 📋 Procedimiento inicialización

### 1. **Alimentación del circuito y shield DXL**
---
   - **Conexión de 5V**:  
     Conecta el voltaje de **5V** a la **terminal de bornera del circuito principal** (ver imagen de referencia). 
      s
     ![Ejemplo conexión 5V](/Docs/images/prueba1.png)  

   - **Conexión de 12V**:  
     Los **12V** deben conectarse a la **bornera del shield DXL** (asegúrate de verificar la polaridad).  

     ![Ejemplo conexión 12V](/Docs/images/prueba2.png)


  - **Conexión USB(Recomendable)**:  
   Conecta el **cable USB** a la ESP32 para permitir una comunicación serial y facilitar un debugging efectivo. 

   ![Ejemplo conexión USB](/Docs/images/prueba2A.png)    



### 2. **Conexión de servomotores Dynamixel**
---
   Los servos Dynamixel requieren tres conexiones básicas:  
   - **V (Voltaje)**: Alimentación del servo.  
   - **G (GND)**: Conexión a tierra.  
   - **D (Data)**: Señal de comunicación.  

   #### Configuración por serie:
   - **Serie XM**:  
     Sigue la disposición de pines mostrada en la siguiente imagen:  
    [![Configuración XM - Haz clic para ver documentación](/Docs/images/XMConexion.png)](https://emanual.robotis.com/docs/en/dxl/x/xm430-w210/#communication-circuit)

   - **Serie MX**:  
     Utiliza esta configuración (nota que el PCB Header es diferente al de la serie AX):  
 
        [![Configuración MX- Haz clic para ver documentación](/Docs/images/MXConexion.png)](https://emanual.robotis.com/docs/en/dxl/mx/mx-106/?_gl=1*1ky8ve0*_gcl_au*OTc2Mjc5MjMzLjE3NDc3NTQ1MTQ.#connector-information)

   - **Serie AX**:  
     Configuración específica para esta serie (comparte PCB Header con MX, pero la asignación de pines varía):  

        [![Configuración MX- Haz clic para ver documentación](/Docs/images/AXConexion.png)](https://emanual.robotis.com/docs/en/dxl/ax/ax-18a/#connector-information)

   ⚠️ **Importante**:  
   - Verifica la serie de tu Dynamixel antes de conectar.  
   - No intercambies las conexiones de voltaje y data para evitar daños.  




### 3. ** Conexión vía Wi-Fi al dispositivo ESP32-AP**
---

Sigue estos pasos para conectarte a la red Wi-Fi del módulo **ESP32-AP** desde diferentes dispositivos:

#### A. **Acceder a la configuración Wi-Fi**
   Dirígete a la sección de **configuración Wi-Fi** de tu dispositivo:  

   ![Interfaz de configuración Wi-Fi](/Docs/images/wifi.png)  


#### 🔹 **Desde una computadora**:
   1. Busca la red llamada **ESP32-AP** en la lista de redes disponibles.  
   2. Haz clic en **ESP32-AP**.  
   3. Ingresa la contraseña cuando se solicite.  

#### 🔹 **Desde un celular (Android/iOS)**:
   1. **Desactiva los datos móviles** para evitar interferencias.  
   2. Ve a **Ajustes > Wi-Fi**.  
   3. Selecciona la red **ESP32-AP**.  
   4. Introduce la contraseña al requerirse.  


### ⚠️ Notas importantes:
- Asegúrate de que el módulo ESP32 esté encendido y emitiendo la red.  
- La contraseña es **sensible a mayúsculas/minúsculas**.  
- Si falla la conexión, reinicia el Wi-Fi del dispositivo o la ESP32.  



### 4.  **Acceso a la interfaz web del ESP32**

#### 1. **Ingreso mediante dirección IP**
1. Abre tu navegador web preferido (Chrome, Firefox, Edge, etc.).
2. En la barra de direcciones, escribe la dirección IP asignada al ESP32.
3. Presiona `Enter` para acceder a la interfaz web.



#### 2. **¿No conoces la dirección IP?**
Sigue estos pasos para encontrarla:

#### 🔍  Usando el Monitor Serial
1. Conecta tu ESP32 al ordenador.
2. Abre el **Monitor Serial** en:
   - Arduino IDE (Herramientas > Monitor Serial)
   - PlatformIO
   - Otro software de comunicación serial (como Putty o CoolTerm)
3. Busca en el output el mensaje que contiene la dirección IP.

```cpp
[Debug] Dirección IP asignada: 192.168.4.1
```
4. Copia esta dirección y pégala en tu navegador.

### ⚠️ Recomendaciones y solución de problemas

### 🔍 Verificaciones previas
- ✅ Asegúrate que:
  - El ESP32 esté correctamente conectado a la red
  - Estés usando la misma red Wi-Fi que el ESP32
  - El firewall de tu sistema no esté bloqueando el acceso

### 🛠️ Si no ves la dirección IP
1. **Revisa la conexión serial**:
   - Verifica que el baud rate coincida en:
     - Tu código (`Serial.begin()`)
     - El monitor serial (generalmente 115200)
2. **Verifica el código**:
   ```cpp
   // Asegúrate de incluir en tu sketch:
   Serial.println("Dirección IP: " + WiFi.localIP());
   ```

## 🛠️ Procedimiento Configuracion 

#### 1. **Cambio de Parametros PID**

1. Selecciona el **servo deseado** desde la interfaz.
2. Dirígete a la sección **`Parámetros de Movimiento`**.
3. Ingresa los valores deseados en la sección **`Parámetros PID`** (proporcional, integral y derivativo).
4. Presiona el botón **`Cambiar Parámetros`** para aplicar los nuevos valores.
5. Aparecerá una alerta con el siguiente mensaje de confirmación:
 ` ✅ Parametros cambiados al servo 1 con  P:Pvalue I:Ivalue D:Dvalue .....`
6. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"servo":"1", "P":"Pvalue", "I":"Ivalue", "D":"Dvalue",.....}//mensaje al evento

   [debug] Parametro modificados al Servo 1: P: PValue I:Ivalue D: Dvalue ...... //Mensaje de recepcion del servidor

   [debug] Servo 1 configurado con nuevos parametros PID ,.... // Mensaje de confirmacion de modificacion
   ```  

#### 2. **Cambio de parametros de velocidad y aceleracion**
1. Selecciona el **servo deseado** desde la interfaz .
2. Dirígete a la sección `Parámetros de Movimiento`.
3. Ingresa los valores deseados en la sección  `Movimiento` (velocidad y aceleración).
4. Presiona el botón  `Cambiar Parámetros` para aplicar los nuevos valores.
5. Aparecerá una alerta con el siguiente mensaje de confirmación: ` ✅ Parametros cambiados al servo 1 con  ..... V:Vvalue A:Avalue `
6. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"servo":"1", ....., "V":"Vvalue","A":"Avalue"}//mensaje al evento

   [debug] Parametro modificados al Servo 1: ......,  //Mensaje de recepcion del servidor

   [debug] Servo 1 configurado con nuevos parametros PID ,...., V :Vvalue , A:Avalue// Mensaje de confirmacion de modificacion
   ```  

#### 3. **Cambio de ID**
1. Selecciona el **servo deseado** desde la interfaz .
2. Dirígete a la sección `ID`.
3. Ingresa el valor deseado en la sección  `Ingrese ID:`.
4. Presiona el botón `Guardar ID` para aplicar los nuevos valores.
5. Aparecerá una alerta con el siguiente mensaje de confirmación:  `ID guardado para Servo 1: IDValue ` 
6. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"servo":"1", "ID":"IDvalue", "baud":"-1"}//mensaje al evento

   [debug] Usando baudrate leído de NVS:  baudFromNVS  //Mensaje de recepcion del servidor

   [debug]   ID actual del servo 1: IDvalue //Debugging sobre el ID Actual

   [debug]  ✅ ID cambiado correctamente. // Mensaje de confirmacion de modificacion

   [debug]  ❌ Error al cambiar el ID.   //Mensaje en caso de error al modificar el ID
   ```  
   En caso que no haya detectado el servo mandara en el Serial el siguiente mensaje :
   ```cpp
   [debug] ❌ Servo no encontrado.
   ```  

#### 4. **Cambio de Baudrate**
1. Selecciona el **servo deseado** desde la interfaz .
2. Dirígete a la sección `Baud Rate`.
3. Seleccione la opcion en la seccion `Seleccione velocidad:`.
4. Presiona el botón `Guardar Baud Rate` para aplicar los nuevos valores.
5. Aparecerá una alerta con el siguiente mensaje de confirmación:  `Baud Rate guardado para Servo 1: BaudValue `
6. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
   
    ```cpp
   [debug] →  {"servo":"1", "ID":"-1", "baud":"BaudValue"} //mensaje al evento

   [debug] Usando baudrate leído de NVS:  baudFromNVS  //Mensaje de recepcion del servidor

   [debug]   ID actual del servo 1: IDvalue //Debugging sobre el ID Actual

   [debug]  ✅ Baudrate cambiado correctamente. // Mensaje de confirmacion de modificacion

   [debug]  ❌ Error al cambiar el baudrate.   //Mensaje en caso de error al modificar el Baud

   ```  
   En caso que no haya detectado el servo mandara en el Serial el siguiente mensaje :
   ```cpp
   [debug] ❌ Servo no encontrado.
   ```  


#### 5. **Escaneo**
1. Dirígete a la sección **`Configuración`**.
2. En el apartado **`Resumen de Servos`**, presiona el botón **`ESCANEAR`**.
3. Aparecerá una alerta con el mensaje:`✅ Iniciando escaneo ...`
4. El escaneo tomará algunos minutos mientras se detectan todos los servos disponibles.
5. Al finalizar, se mostrará una alerta con el mensaje:
 `Datos actualizados correctamente en la tabla..` 
 Además, los resultados del escaneo se presentarán en una tabla organizada.
 6. En la pestaña individual de cada servo, verás un ícono de estado:
- ✅ Una palomita indica que el servo está **operativo y fue detectado correctamente**.
- ❌ Un tache indica que el servo **no responde o está desconectado**.


## 🔄 Procedimiento Movimiento Servos

#### 1. **Movimiento sencillo**
1. Selecciona el **servo deseado** desde la interfaz .
2. Dirígete a la sección `Movimiento Inmediato`.
3. Selecciona cómo deseas trabajar la posición del servo usando los **botones de opción**:
- **Grados**: 0° a 360°
- **Unidades de encoder**: 0 a 4095
4. Ingresa el valor deseado en la sección  `Posición:`
5. Presiona el botón `Mover` para mandar el comando.
6. Aparecerá una alerta con el siguiente mensaje de confirmación, según el tipo de unidad seleccionada:
`✅ Movimiento enviado al Servo 1 con 200°`
o bien 
`✅ Movimiento enviado al Servo 2 con 2000 units.`

   Si ingresas un valor inválido, se mostrará el siguiente mensaje de advertencia:
   `⚠️ Ingresa un número válido.`
7. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"servo":"1","type":"typevalue","value":"Posvalue"}//mensaje al evento

   [debug] Moviendo el  Servo 1: 200 angle   //Mensaje de recepcion del servidor

   [debug] Servo 1 termino de moverse// Mensaje de finalizacion del movimiento
   ```  


#### 2. **Agregar punto en trayectoria**
1. Selecciona el **servo deseado** desde la interfaz .
2. Dirígete a la sección `Configuración Trayectoria`.
3. Selecciona cómo deseas trabajar la posición del servo usando los **botones de opción**:
- **Grados**: 0° a 360°
- **Unidades de encoder**: 0 a 4095
4. Ingresa el valor deseado en la sección  `Posición:`
5. Presiona el botón `Punto agregado` para guardar el punto.
6. Aparecerá una alerta con el siguiente mensaje de confirmación, según el tipo de unidad seleccionada:
`✅ Punto agregado para el Servo 1 con 200°`
o bien 
`✅ Punto agregado para el Servo 2 con 2000 units.`

   Si ingresas un valor inválido, se mostrará el siguiente mensaje de advertencia:
   `⚠️ Ingresa un número válido.`
1. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"servo":"1","type":"typevalue","value":"Posvalue"}//mensaje al evento

   [debug] Punto agregado al Servo 1: 200 angle   //Mensaje de recepcion del servidor

   [debug] Punto agregado correctamente // Mensaje de confirmacion de guardado
   ```  
   ⚠️ **Advertencia:** Cada servo puede almacenar hasta 10 puntos de trayectoria.
   Si alguno supera ese límite, se mostrará el siguiente mensaje:

   ```cpp
   [debug] Error: no se puede agregar más puntos  // Mensaje de error de guardado
   ```

#### 3. **Ejecutar trayectoria**

1. Dirígete a la parte inferior de la pagina
2. Presiona el botón `Ejecutar secuencia alternada` para guardar el punto.
3. Aparecerá una alerta con el siguiente mensaje :
`✅ Ejecutando secuencia alternada...`
4. Además, en el monitor serial se enviarán los siguientes mensajes para depuración y confirmación:
    ```cpp
   [debug] →  {"start":"1"}  //mensaje al evento

   [debug] Punto maximo: 2  //Mensaje de recepción del servidor, indicando la longitud máxima de la trayectoria configurada (en este caso, 2 puntos).

   [debug] Servo 5 inactivo o sin punto, saltando... //El sistema detecta que el servo 5 no está activo o no tiene puntos definidos en la trayectoria, por lo que omite su ejecución.

   [debug] moviendo servo 1 a 300 Angle //El servo 1 recibe la instrucción de moverse a una posición específica (ángulo 300).

   [debug] Servo 1 llego al punto 1 //Confirmación de que el servo 1 ha alcanzado exitosamente el primer punto de la trayectoria.

   [debug] Servo 2 llego al punto 1 //Confirmación de que el servo 2 ha alcanzado exitosamente el primer punto de la trayectoria.

   [debug] Punto 1 completado  //Indica que todos los servos involucrados han completado la ejecución del Punto 1 de la trayectoria.

   [debug] Secuencia completada // Mensaje final que confirma la ejecución exitosa de toda la trayectoria programada.
   ```  

## 🧰 Configuración del entorno de desarrollo
 ### Requisitos del sistema
- Sistema operativo: Windows 10/11, Ubuntu 22.04 LTS o macOS Ventura
- Espacio en disco: mínimo 500 MB
- Conexión a internet (solo para la instalación)

 ### Software necesario
- [Visual Studio Code](https://code.visualstudio.com/)
- [Arduino IDE 1.8.18](https://www.arduino.cc/en/software/OldSoftwareReleases/) 
  - Board: ESP32 Dev Module (Instalar desde el Gestor de Placas como **esp32** by **espressif Systems**)
  
### Dependencias o librerías


#### Librerías externas
- [ESPAsyncWebServer v1.2.4](https://github.com/ESP32Async/ESPAsyncWebServer) - Servidor web asíncrono.
- [Arduino_JSON v0.2.0](https://github.com/arduino-libraries/Arduino_JSON) - Soporte para JSON (legacy).
- [Dynamixel2Arduino](https://github.com/ROBOTIS-GIT/Dynamixel2Arduino) - Control de servomotores Dynamixel.

#### Librerías integradas en ESP32 (Core 3.0.1+)
- **SPIFFS** -Acceso via (`#include <SPIFFS.h>`).
- **nvs_flash** - Acceso via `Preferences.h`.

#### Herramientas
- [SPIFFS Plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin) - Subir archivos al ESP32 (Arduino IDE).
  - [Video tutorial](https://youtu.be/PF_URnKhsNQ?si=sJlZXYrpXU3g78sV).



### Compilacion y carga del Firmware

#### SPIFFS

Creacion del repositorio  para SPIFFS

1.En la  

## vip
## Estructura del Código

El sistema de control remoto del brazo robótico está construido con una arquitectura modular dividida en dos bloques principales:

1. **Bloque embebido**: ejecutado en el microcontrolador ESP32.
2. **Bloque web**: interfaz gráfica accesible desde un navegador.

Ambos bloques se comunican mediante el protocolo HTTP y tecnologías web modernas, asegurando una interacción en tiempo real sin necesidad de recargar la página.
---
### 1. Archivos principales

#### `index.html` – Interfaz web del usuario
Define la estructura de la interfaz que el usuario visualiza en el navegador. Incluye:

- Encabezados (`<h1>`, `<h2>`, `<h3>`)
- Formularios de control por servo
- Pestañas interactivas
- Imágenes dinámicas por sección
- Tabla resumen de estado de cada servo

> Usa HTML semántico para facilitar el mantenimiento y la accesibilidad.
---
#### `styles.css` – Diseño visual con layout responsivo

- Define el estilo visual general (colores, fuentes, márgenes, distribución).
- Utiliza **variables CSS** en `:root` para personalizar fácilmente temas y colores.
- Divide la pantalla en dos secciones:  
  - `.controls` (panel izquierdo para configuración)
  - `.image-container` (panel derecho con imágenes de referencia)
- Incluye efectos `hover`, pestañas activas, diseño responsivo y decoración con líneas laterales.

> El diseño es moderno, profesional y adaptable a escritorio o móvil.
---
#### `normalize.css` – Estandarización de estilos base

- Restablece los estilos por defecto del navegador.
- Garantiza uniformidad en tipografías, márgenes, botones, inputs, etc.
- Mejora la compatibilidad visual entre navegadores (Chrome, Firefox, Edge, Safari).

> No afecta el diseño personalizado, pero es fundamental para evitar inconsistencias visuales.
---
#### `script.js` – Lógica de interacción y envío de comandos

- Controla el cambio entre pestañas (`openTab`).
- Captura datos de formularios y los envía al ESP32 vía `XMLHttpRequest`.
- Escucha eventos del servidor (`EventSource`) para mantener la página actualizada.
- Actualiza íconos de estado, muestra alertas y manipula el DOM dinámicamente.

> Contiene funciones clave como `submitForm()`, `addPoint()`, `guardarID()`, `actualizarEstadoServo()`.
---
#### `main.ino` o `firmware.ino` – Controlador embebido en el ESP32

- Programado en C++ para el entorno Arduino.
- Carga librerías como `ESPAsyncWebServer`, `SPIFFS`, `Dynamixel2Arduino`.
- Define rutas HTTP (`/move`, `/addPoint`, etc.) y lanza eventos para la interfaz.
- Usa una máquina de estados para coordinar movimientos secuenciales.

> Toda la lógica embebida del sistema vive en este archivo y sus módulos `.hpp`.
---
### 2. Organización en SPIFFS

El sistema utiliza **SPIFFS (SPI Flash File System)** para almacenar los archivos web en la memoria interna del ESP32.
 ### Estructura de la carpeta `/data` (SPIFFS)

| Archivo             | Descripción                                                  |
|---------------------|--------------------------------------------------------------|
| `index.html`        | Interfaz principal del sistema accesible desde el navegador. |
| `styles.css`        | Archivo de estilos personalizados (layout, colores, fuentes).|
| `normalize.css`     | Hoja de estilos base para estandarizar visualización entre navegadores. |
| `script.js`         | Lógica de interacción entre el usuario y el ESP32.           |
| `fondo.png`         | Imagen de fondo usada en todo el sistema.                    |
| `iconoSI.png`       | Icono mostrado cuando un servo está conectado correctamente. |
| `iconoNO.png`       | Icono mostrado cuando un servo no está conectado.            |
| `servo1.jpeg`       | Imagen representativa del Servo 1 (usada en la pestaña 1).   |
| `servo2.jpeg`       | Imagen representativa del Servo 2 (usada en la pestaña 2).   |
| `servo3.jpeg`       | Imagen representativa del Servo 3 (usada en la pestaña 3).   |
| `servo4.jpeg`       | Imagen representativa del Servo 4 (usada en la pestaña 4).   |
| `confi.jpeg`        | Imagen usada en la pestaña de configuración general.         |



**Subida al ESP32**:
- Instala el plugin [ESP32 Sketch Data Upload](https://github.com/me-no-dev/arduino-esp32fs-plugin).
- Coloca todos los archivos en `/data`.
- Ejecuta desde el menú: `Herramientas → ESP32 Sketch Data Upload`.

> Esta técnica permite que el ESP32 sirva los archivos directamente sin depender de un servidor externo.

## Diagrama de estados 

PENDIENTES

## Manual del Desarrollador

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
1. Abre `server.hpp` o el archivo `.ino` correspondiente.
2. Agrega una nueva ruta:
   ```cpp
   server.on("/nuevaRuta", HTTP_GET, [](AsyncWebServerRequest *request){
     request->send(200, "text/plain", "OK");
   });
   ```
3. (Opcional) Lanza un evento:
   ```cpp
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
- Conecta el sensor y declara su pin:
  ```cpp
  const int sensorPin = 34;
  ```
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
 






