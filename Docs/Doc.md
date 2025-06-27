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
La interfaz web de este proyecto no depende de servidores externos, sino que se **almacena directamente en la memoria flash del ESP32** mediante el sistema de archivos SPIFFS (*Serial Peripheral Interface Flash File System*). Esto permite que el ESP32 sirva archivos estáticos (como HTML, CSS, JS e imágenes) de forma autónoma a través del navegador web de cualquier dispositivo conectado a su red.

A continuación se detalla el proceso completo para preparar, configurar y subir correctamente los archivos al ESP32 utilizando SPIFFS.


**Instalacion de Plugin**
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

Verifica que esté visible antes de continuar con los pasos siguientes.


**Creacion del repositorio  para SPIFFS**
1. Crea una carpeta llamada `data` con la siguiente estructura:
  
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
2. Abre el **proyecto en el Arduino IDE**.
3. Asegúrate de seleccionar la **placa correcta** desde el menú:
   ```
   Herramientas > Placa > ESP32 Dev Module
   ```
4. Selecciona el **puerto correcto** donde está conectado tu ESP32:
   ```
   Herramientas > Puerto > COMX o /dev/ttyUSBX
   ```
5. Conecta tu ESP32 a la computadora mediante USB.

6. Ahora, haz clic en el menú:
   ```
   Herramientas > ESP32 Sketch Data Upload
   ```
7. Espera unos segundos mientras se carga el sistema de archivos. Verás en el monitor de salida mensajes similares a:
    ```
    [SPIFFS] Uploading file: /index.html
    [SPIFFS] Uploading file: /styles.css
    ...
    [SPIFFS] Total file size: 78.2 KB
    [SPIFFS] Success!
    ```

 **Importante:**
- El nombre de la carpeta debe ser exactamente `data` (todo en minúsculas).
- Todos los archivos que se usarán en el navegador (como HTML, CSS, JS e imágenes) deben estar dentro de esta carpeta.


#### ESP32
---
El firmware es la parte del proyecto que corre directamente sobre el microcontrolador ESP32. Este código es responsable de crear el servidor web, controlar los servomotores Dynamixel, gestionar los archivos almacenados en SPIFFS y comunicarse con la interfaz del usuario.

Para compilar y cargar correctamente el firmware en el ESP32 desde el **Arduino IDE**, es fundamental seguir cuidadosamente los pasos descritos a continuación.

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
4. Conecta tu ESP32 por USB a la computadora.
5. Luego en Arduino IDE ve a:
   ```
   Herramientas > Puerto > COMx (Windows) o /dev/ttyUSBx (Linux/macOS)
   ```

> Asegúrate de que **el puerto cambie** al conectar y desconectar el ESP32. Si no aparece, puede deberse a un problema de drivers.

Ya configurado el puerto y la placa, debemos seguir los siguientes pasos para compilar y subir el firmware a la `Esp32`:

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
Cargando Sistema de Archivos SPIFFS 
Cargado con éxito
Servo MX id_Mx configurado en posición (Protocolo 1.0). No Modelo: modelNumMX 
Servo id configurado en posición (Protocolo 2.0).No Modelo:modelNumXM
Servo id configurado en posición (Protocolo 2.0).No Modelo:modelNumXM
Dynamixel AX18A encontrado y listo.
Configuracion completa.

```
Adicionalmente, se desplegará una lista binaria (valores 1 o 0) en el monitor serial que representa el estado lógico de cada servomotor. Un valor de 1 indica que el servo está activo, mientras que un valor de 0 señala que está inactivo, conforme a la configuración de inicialización definida al momento de arranque del microcontrolador ESP32
### Posibles errores y cómo solucionarlos

| Error en consola                       | Causa probable                                       | Solución sugerida                                         |
|----------------------------------------|------------------------------------------------------|-----------------------------------------------------------|
| `SPIFFS mount failed`                  | No se inicializó correctamente `SPIFFS.begin()`      | Verifica código y asegúrate de que `SPIFFS.begin(true)` esté presente |
| `No such file or directory`            | Librería faltante                                    | Instala la librería desde el Gestor de Bibliotecas        |
| `Failed to connect to ESP32`           | Puerto incorrecto o mal contacto                     | Revisa cable USB, reinicia ESP32, cambia puerto           |
| `Guru Meditation Error` (core dump)    | Error crítico en tiempo de ejecución                 | Verifica punteros, delays, accesos inválidos              |


## 🏗️Arquitectura del sistema

### Estructura del Código

El sistema de control remoto del brazo robótico está construido con una arquitectura modular dividida en dos bloques principales:

1. **Bloque embebido**: ejecutado en el microcontrolador ESP32.
2. **Bloque web**: interfaz gráfica accesible desde un navegador.

Ambos bloques se comunican mediante el protocolo HTTP y tecnologías web modernas, asegurando una interacción en tiempo real sin necesidad de recargar la página.

### Archivos principales
---
### 1. ***Bloque web***
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

---
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

### 2. ***Bloque embebido***
| Archivo             | Descripción                                                  |
|---------------------|--------------------------------------------------------------|
| `ServidorWebDyna.ino`        | Gestor de la maquina de estados e iniciador del servidor. |
| `DxlConfig.hpp`        | Módulo responsable de gestionar todas las acciones relacionadas con los servomotores Dynamixel, incluyendo movimiento individual, escaneo de dispositivos, modificación de parámetros, ejecución de secuencias,registro de puntos de trayectoria,enytre otros.|
| `Server.hpp`     | Módulo responsable de procesar las solicitudes HTTP entrantes desde el cliente y de activar los eventos asociados dentro del sistema. |
| `json.hpp`     | Módulo encargado de generar respuestas en formato JSON para operaciones relacionadas con el control de servos Dynamixel. |
| `spiffs_uli.hpp`     | Modulo encargado de inicializar la memoria SPIFFS. |
| `wifi_Dxl.hpp`     | Modulo encargado de inicializar la conexion Wi-Fi mediante AP o STA. |
| `variables.h`     | Archivo donde se declaran las variables globales necesarias para la operacion del sistema. |
---
#### `ServidorWebDyna.ino` – Gestor de la maquina de estados e iniciador del servidor. 
Este módulo se encarga de la inicialización de todos los elementos necesarios para el funcionamiento del servidor web y del control de los servomotores Dynamixel. Además, implementa la lógica de la máquina de estados para gestionar las acciones complejas del sistema, como el movimiento individual, la ejecución de secuencias y el escaneo de servos.

- Invoca las funciones necesarias para la configuración e inicialización de módulos externos.

- Inicializa la comunicación serial para depuración.

- Establece la conexión Wi-Fi, ya sea en modo AP o STA.

- Monta el sistema de archivos SPIFFS para el manejo de archivos locales.

- Inicia el servidor web asíncrono que atiende las solicitudes del cliente.

- Evalúa banderas de control (flags) para ejecutar acciones dentro de la máquina de estados finitos.


> Codigo principal

---

#### `DxlConfig.hpp` – Gestor de las acciones relacionadas con los servos Dynamixel

Este módulo gestiona las solicitudes del firmware para realizar la accion solicitada, ya sea configuracion inicial de los servomotores, escaneo de servos, movimiento simple, ejecucion de secuencias, cambio de parametros.

- ***`InitconfigDXL()`*** : 

  Función que configura todos los servomotores Dynamixel al inicio del programa, utilizando los datos almacenados en la memoria NVS (almacenamiento no volátil) o, en su defecto, los valores contenidos en estructuras de datos internas. Esta configuración puede incluir ID, protocolo, velocidad en baudios, límites de movimiento, entre otros parámetros necesarios para el correcto funcionamiento de cada servo.

- ***`IndConfigDXL(int index)`*** :

   Función que configura un servomotor Dynamixel utilizando la información almacenada en la estructura `scanDXL`, con base en el índice recibido como parámetro. Esta estructura contiene los datos obtenidos previamente mediante la función `scanServoDxl()`, como el ID del servo, protocolo de comunicación, velocidad de transmisión (baudrate) y número de modelo.


- ***`scanServoDxl()`***:
  
   Función que escanea la comunicacion entre Dynamixel probando ambos protocolos de comunicación (1.0 y 2.0) y recorriendo los posibles valores de baudrate definidos en el arreglo `baud[13]`. Para cada combinación válida, utiliza la función `scan()` de la librería Dynamixel2Arduino para detectar actividad en el bus. Si se detecta un dispositivo, se realiza un barrido de IDs del 0 al 253 mediante la función `ping()`, registrando en el arreglo `scanDXL` la información del servo encontrado. El proceso continúa hasta detectar los 4 servos del sistema o agotar las combinaciones posibles, retornando el arreglo `scanDXL` con los dispositivos detectados.

- ***`reorderScanDXL(ServoInfo scanDXL[], int count_found,  int modeloOrden[], int ordenSize)`***:  
  Función que reorganiza los elementos del arreglo `scanDXL` (resultado del escaneo de servos) según un orden definido en el arreglo `modeloOrden`, el cual especifica el número de modelo deseado para cada posición. Compara cada elemento encontrado con los valores de `modeloOrden` y reordena el arreglo para alinear la disposición física de los servos con el orden lógico esperado por el sistema. Devolviendo el arreglo  `scanDXL` con el orden deseado.

- ***`SCANFlag()`*** : 
  
  Función invocada a partir de una solicitud HTTP del cliente para iniciar el escaneo de servomotores. Su propósito es activar la bandera `scanMode`, la cual es evaluada dentro del ciclo principal del programa y utilizada por la máquina de estados finitos para ejecutar el proceso de escaneo.


- ***`moveDxl(int index, String type, int valuePos, bool simple)`***: 
  
  Función encargada de enviar el comando de posición objetivo al servomotor especificado, ya sea en formato de ángulo o como valor interno del encoder. Puede ser invocada desde una solicitud HTTP (movimiento simple) o desde la máquina de estados (ejecución de secuencia).
Cuando se invoca desde una **solicitud HTTP** (movimiento simple), activa la bandera `moveSimple`, la cual es evaluada por la máquina de estados para iniciar el seguimiento del movimiento. En cambio, si se llama desde un **estado dentro de una secuencia**, solo envía el comando de posición objetivo, sin activar la bandera `moveSimple`  y el monitoreo se realiza en estados posteriores del ciclo de control.
 

- ***`addPoint(int index, String type, int valuePos)`***: 
  
  Función encargada de registrar un nuevo punto de trayectoria para el servomotor identificado por `index`, a partir de una solicitud del cliente. El punto se almacena en el arreglo `puntos` dentro de la estructura `servos[]`, incluyendo el tipo de movimiento (`type`) y el valor de posición (`valuePos`). Si el servo ya cuenta con 10 puntos registrados, la función no añade nuevos valores, respetando el límite máximo definido.

- ***`executeSequence()`***: 
  
  Función encargada de analizar los puntos de trayectoria registrados en todos los servomotores para determinar la dimensión total de la secuencia (tomando como referencia el servo con mayor número de puntos). Posteriormente, activa la bandera `ejecutandoSecuencia`, lo que permite a la máquina de estados salir del estado IDLE e iniciar la ejecución paso a paso de la secuencia definida.

- ***`changeMoveParamet(int index,float Pvalue,float Ivalue,float Dvalue,int Vvalue,int Avalue)`***: 
  
  Función encargada de actualizar los parámetros de control de movimiento del servomotor especificado por `index`, incluyendo los valores PID, velocidad y aceleración. Estos valores se escriben directamente en la tabla de control del servo mediante `writeControlTableItem()`, y además se almacenan en la estructura `servos[]` y en la memoria NVS para su persistencia.

- ***`getBaudValue(int index, int desiredBaud)`***: 
  
  Función que retorna el valor codificado correspondiente al `desiredBaud` necesario para escribir correctamente en la memoria del servomotor Dynamixel con protocolo 1.0. Este valor es requerido para configurar la velocidad de comunicación en la tabla de control interna del dispositivo. **Advertencia**: solamente esta soportado para modelo de MX-106 (1.0).


- ***`chanceServoParamet(int index, int newBaud, int newID)`***: 
  
  Función encargada de modificar el ID y/o el baudrate del servomotor seleccionado por el cliente. Primero verifica si hay comunicación con el dispositivo, y en caso afirmativo, realiza el cambio solicitado. Para servomotores con protocolo 1.0, utiliza la función `getBaudValue(...)` y `write()` para escribir directamente en la memoria del servo. En el caso de servos con protocolo 2.0, la actualización del baudrate se realiza mediante la función `setBaudrate()`.
 

> Implementa las funciones de configuracion y control para los servomotores DYNAMIXEL mediante la biblioteca Dynamixel2Arduino


---

#### `Server.hpp` –  Gestor de las solicitudes HTTP entrantes desde el cliente  y eventos
Este módulo configura e inicializa un servidor web asíncrono sobre la ESP32 utilizando la librería `ESPAsyncWebServer`. Define múltiples rutas HTTP (`endpoints`) que permiten al cliente realizar operaciones sobre los servomotores Dynamixel. Además, integra un canal de comunicación mediante Server-Sent Events (SSE) para enviar respuestas en tiempo real al cliente, incluyendo confirmaciones de acción, actualizaciones visuales o monitoreo del estado del sistema. Al establecer la conexión, se sirve la interfaz web desde SPIFFS y se notifica al cliente el estado actual de cada servo.

- ***`/move`***:
  
  Ruta HTTP que permite recibir parámetros de movimiento a través de la URL, por ejemplo: `/move?servo=1&type=goal_position&value=300`. Al recibir la solicitud, se extraen los parámetros `servo`, `type` y `value`, los cuales se imprimen por el puerto serial como mecanismo de depuración. Posteriormente, los valores se convierten a los tipos de datos adecuados (por ejemplo, `String` a `int`) y se invoca la función **`moveDxl()`** para enviar el comando de movimiento al servomotor correspondiente, indicando que se trata de un movimiento simple mediante un parámetro de control. Finalmente, se genera un objeto JSON con la función **`moveServoJSON()`** y se envía al cliente web a través de Server-Sent Events (SSE), utilizando el evento nombrado como `servo{# de servo}`, lo que permite visualizar y monitorear el estado del comando en tiempo real desde la interfaz.
  
-  ***`/addPoint`***: 
  
   Ruta HTTP que permite registrar un nuevo punto de trayectoria para un servomotor específico. A través de la URL se reciben los parámetros `servo`, `type` y `value`, por ejemplo: `/addPoint?servo=1&type=angle&value=90`. Estos valores se extraen de la solicitud y se imprimen por el puerto serial como mecanismo de depuración. Posteriormente, se convierten a los tipos de datos adecuados y se invoca la función **`addPoint()`**, la cual almacena el punto en la estructura interna del servo correspondiente. Finalmente, se genera un objeto JSON con la función **`addPointJSON()`** y se envía al cliente web mediante Server-Sent Events (SSE) bajo el canal `pointAdd{# de servo}`, permitiendo visualizar el registro del punto desde la interfaz.
  
-  ***`/moveParamet`***: 
  
   Ruta HTTP que permite modificar los parámetros de control de movimiento de un servomotor específico, incluyendo los valores PID (`P`, `I`, `D`), la velocidad (`v`) y la aceleración (`a`). Al recibir la solicitud, se extraen los parámetros desde la URL, por ejemplo: `/moveParamet?servo=1&p=20&i=10&d=5&v=100&a=50`, y se imprimen por el puerto serial para fines de depuración. Posteriormente, los valores se convierten a sus tipos numéricos correspondientes y se invoca la función **`changeMoveParamet()`**, que escribe dichos parámetros en la tabla de control del servo, además de almacenarlos en la estructura interna y en la memoria NVS. Finalmente, se genera un objeto JSON con **`changeMoveParametJSON()`** y se envía al cliente mediante Server-Sent Events (SSE) usando el canal `MoveParam{# de servo}`, para reflejar los cambios en la interfaz en tiempo real.
  
-   ***`/IDChance`***: 
  
      Ruta HTTP que permite modificar el ID de un servomotor Dynamixel seleccionado. Al recibir la solicitud con los parámetros `servo` e `id` (por ejemplo: `/IDChance?servo=1&id=3`), se extraen los valores, se imprimen por el puerto serial y se invoca la función **`chanceServoParamet()`**. En esta llamada, se pasa el nuevo ID deseado y un valor `-1` para el baudrate, indicando que este último no debe modificarse. Una vez actualizado el ID del servo, se genera un objeto JSON mediante **`changeServoParametJSON()`** y se envía al cliente a través de Server-Sent Events (SSE) usando el canal `ServoParam{# de servo}`, permitiendo reflejar el cambio en tiempo real en la interfaz.
   

-   ***`/BaudChance`***: 
  
      Ruta HTTP que permite modificar el baudrate (velocidad de comunicación) de un servomotor Dynamixel. Al recibir la solicitud con los parámetros `servo` y `baud` (por ejemplo: `/BaudChance?servo=2&baud=57600`), se extraen los valores, se imprime la operación por el puerto serial y se invoca la función **`chanceServoParamet()`**. En esta llamada se pasa el nuevo baudrate deseado y un valor `-1` para el ID, indicando que este no será modificado. Tras realizar el cambio, se genera un objeto JSON mediante **`changeServoParametJSON()`** y se envía al cliente a través de Server-Sent Events (SSE) usando el canal `ServoParam{# de servo}`, lo que permite actualizar la interfaz en tiempo real con la nueva configuración.


-  ***`/Start`***:  
  
   Ruta HTTP que permite iniciar la ejecución de una secuencia de movimiento previamente definida para los servomotores. Al recibir la solicitud, se imprime un mensaje en el puerto serial como confirmación, y se invoca la función **`executeSequence()`**, la cual organiza y activa la secuencia a través de la máquina de estados. Posteriormente, se genera un objeto JSON con **`startSequenceJSON()`** y se envía al cliente web mediante Server-Sent Events (SSE) usando el canal `startSeq`, notificando así que la ejecución de la secuencia ha comenzado.
  

- ***`/Scan`***: 

  Ruta HTTP que permite iniciar el proceso de escaneo de servomotores conectados a la red Dynamixel. Al recibir la solicitud, se imprime un mensaje de diagnóstico por el puerto serial y se invoca la función **`SCANFlag()`**, la cual activa una bandera que será interpretada por la máquina de estados para ejecutar el escaneo. Este escaneo permite detectar automáticamente los servos disponibles, sus IDs, protocolos y baudrates. Finalmente, se responde al cliente con un mensaje `OK` confirmando la recepción de la solicitud.

- ***`/pingtest`***:  
  Ruta HTTP de prueba que responde con el texto `"pong"`, utilizada para verificar la disponibilidad y tiempo de respuesta del servidor. Sirve como herramienta básica para diagnóstico de conectividad entre el cliente y la ESP32.



- ***`/reportLatencia`***:  
   Ruta HTTP que permite al cliente reportar el valor de latencia medida durante la comunicación. Si el parámetro `valor` está presente en la solicitud (por ejemplo: `/reportLatencia?valor=123`), el valor se imprime por el puerto serial y se responde con un mensaje `"OK"`. En caso de que el parámetro no sea proporcionado, se envía un código de error `400` indicando que falta el parámetro. Además, se activa la bandera `check`, posiblemente utilizada para validaciones posteriores dentro del ciclo principal del sistema. Esta parte se puede activar al descomentar en la maquina de estados el gestor de latencia.

- ***Conexión de cliente y envío inicial por SSE***:  
Al establecerse una nueva conexión con el cliente a través de Server-Sent Events (SSE), se ejecuta una función de callback definida mediante `events.onConnect(...)`. Si el cliente se reconecta, se recupera su último ID de evento recibido (`client->lastId()`) y se imprime por el puerto serial como referencia de depuración. Luego, se envía un mensaje inicial de saludo (`"Hola!"`) y, a continuación, se recorre un ciclo para enviar al cliente el estado actual de los cuatro servomotores mediante la función **`chanceIconJSON()`**, asociando cada mensaje a un evento identificado como `chanceIcon{# de servo}`.  
Finalmente, el manejador de eventos SSE es registrado en el servidor con `server.addHandler(&events)` y el servidor web asíncrono se inicia con `server.begin()`.

 >  Permite que el cliente web reciba datos iniciales de estado sin necesidad de realizar solicitudes adicionales, facilitando una actualización automática y eficiente de la interfaz al conectarse al sistema.

---
 #### `json.hpp` –  Modulo generador de formatos JSON
 Este módulo agrupa un conjunto de funciones responsables de generar estructuras de datos en formato **JSON**, utilizadas para la comunicación entre la ESP32 y el cliente web mediante eventos SSE (Server-Sent Events).  Cada función construye un objeto JSON con los datos recibidos, lo convierte en una cadena de texto y lo imprime por el puerto serial para fines de depuración. Estos JSON son fundamentales para mantener sincronizada la interfaz gráfica del cliente con el estado actual del sistema.

- ***moveServoJSON(String servo, String type, String value)*** :
  
  Función encargada de generar un objeto JSON que representa un comando de movimiento para un servomotor. Recibe como parámetros el identificador del servo (`servo`), el tipo de comando (`type`) y el valor objetivo (`value`). Esta información se organiza en una estructura JSON con las claves correspondientes y se convierte en una cadena de texto que se imprime por el puerto serial y se retorna para su envío al cliente web a través de SSE.

- ***addPointJSON(String servo, String Type, String value)*** :
  
   Función encargada de generar un objeto JSON que representa un nuevo punto de trayectoria para un servomotor. Recibe como parámetros el identificador del servo (`servo`), el tipo de movimiento (`Type`) y el valor de posición (`value`). Los datos se encapsulan en una estructura JSON, se convierten a cadena de texto y se imprimen por el puerto serial para depuración. El resultado se retorna para ser enviado al cliente web mediante SSE.



- ***changeMoveParametJSON(String servo, String P, String I, String D, String V, String A)*** :
  
   Función encargada de generar un objeto JSON que encapsula los parámetros de control de movimiento de un servomotor. Recibe como entrada el identificador del servo (`servo`), los valores PID (`P`, `I`, `D`), así como la velocidad (`V`) y la aceleración (`A`). Los datos se estructuran en formato JSON, se convierten a cadena de texto y se imprimen por el puerto serial como mecanismo de depuración. El resultado es retornado para su transmisión al cliente web a través de eventos SSE.


- ***changeServoParametJSON(String servo, String id, String baud)*** :
  
   Función que genera un objeto JSON con los nuevos parámetros de identificación y comunicación de un servomotor. Recibe el número de servo (`servo`), el nuevo ID (`id`) y el nuevo baudrate (`baud`). Esta información se organiza en un objeto JSON, se convierte a cadena de texto y se imprime por el puerto serial como parte del proceso de depuración. El resultado se retorna para su envío al cliente web mediante eventos SSE.


- ***startSequenceJSON()*** :
  
   Función que genera un objeto JSON utilizado para indicar el inicio de una secuencia de movimiento de servomotores. El campo `"start"` se establece con el valor `"1"` como señal de activación. El objeto JSON resultante se convierte en una cadena de texto, se imprime por el puerto serial para propósitos de depuración y se retorna para su envío al cliente web mediante eventos SSE.



- ***scanResultsJSON(ServoInfo servos[], int count)*** :
  
   Función que genera un arreglo JSON con la información de los servomotores detectados durante el escaneo. Recorre los primeros `count` elementos del arreglo `servos[]`, extrayendo para cada uno su ID, protocolo, baudrate y número de modelo, y los encapsula como objetos dentro de un array JSON. El resultado se convierte a cadena de texto, se imprime por el puerto serial para depuración, y se retorna para su posterior envío al cliente web mediante eventos SSE.



- ***chanceIconJSON(String servo,String flag)*** :
  
   Función que genera un objeto JSON para indicar el estado visual (ícono o indicador) de un servomotor específico en la interfaz del cliente. Recibe el número de servo (`servo`) y una bandera (`flag`) que representa su estado actual. El objeto JSON resultante se convierte en cadena de texto, se imprime por el puerto serial para fines de depuración y se retorna para su transmisión mediante eventos SSE al cliente web. Estos JSON son fundamentales para mantener sincronizada la interfaz gráfica del cliente con el estado actual del sistema.


 > Estas funciones permiten estructurar y transmitir información crítica del sistema en formato JSON, facilitando la comunicación en tiempo real entre la ESP32 y el cliente web mediante eventos SSE.


---
#### `spiffs_uli.hpp` –  Inicialización del sistema de archivos SPIFFS

Este módulo se encarga de inicializar el sistema de archivos SPIFFS (Serial Peripheral Interface Flash File System) en la ESP32. Mediante la función `spiffs_init()`, se monta el sistema de archivos interno para permitir el acceso a recursos almacenados localmente, como archivos HTML, CSS, JS e imágenes utilizados por la interfaz web. Si la carga del sistema de archivos falla, se muestra un mensaje de error por el puerto serial; en caso contrario, se confirma su carga exitosa. Esta operación es fundamental para habilitar la comunicación entre el servidor web y la interfaz del usuario.



 >  La correcta inicialización del sistema de archivos SPIFFS es esencial para garantizar que la interfaz web y otros recursos estáticos puedan ser servidos por la ESP32. Esta operación debe ejecutarse antes de iniciar el servidor web para asegurar el acceso completo a los archivos necesarios durante la ejecución del sistema.

 ---

#### `wifi_Dxl.hpp` –  Inicialización de la conexion Wi-Fi

Este módulo gestiona la configuración de conectividad Wi-Fi de la ESP32, permitiéndole operar tanto en modo punto de acceso (AP) como en modo estación (STA). La función `wifi_AP_init()` configura la ESP32 como un Access Point local con los parámetros de SSID y contraseña proporcionados, realizando múltiples intentos hasta lograr una IP válida. Por otro lado, `connectToWiFi()` permite conectar la ESP32 a una red Wi-Fi externa utilizando credenciales predefinidas, implementando un mecanismo de espera y verificación de estado de conexión. Este módulo es esencial para establecer la comunicación entre el servidor web embebido y los dispositivos cliente.



- ***wifi_AP_init(const char* ssid, const char* pass)***:

   Función encargada de configurar la ESP32 como punto de acceso (Access Point) utilizando el SSID y la contraseña proporcionados. Realiza hasta cinco intentos para establecer correctamente el AP, verificando que se haya asignado una dirección IP válida. Si la configuración es exitosa, imprime la IP asignada por el AP. En caso contrario, reporta errores en el proceso de configuración a través del puerto serial. Esta función permite establecer una red Wi-Fi local propia, facilitando la conexión directa de dispositivos cliente sin depender de una red externa.

- ***connectToWiFi()*** :

   Función encargada de conectar la ESP32 a una red Wi-Fi externa utilizando un SSID y contraseña predefinidos. Inicia la conexión mediante `WiFi.begin()` y espera hasta 10 segundos para verificar si se ha establecido correctamente. Durante este tiempo, muestra el progreso por el puerto serial. Si la conexión es exitosa, imprime la dirección IP asignada por el router. En caso de fallo, informa el error por el mismo canal. Esta función permite integrar la ESP32 a una red local existente, facilitando la comunicación con dispositivos en la misma red.



> Aunque este módulo incluye funciones tanto para operar en modo Access Point como en modo Estación (STA), actualmente el sistema utiliza únicamente la conexión por AP para establecer una red local directa entre la ESP32 y el cliente. Esto permite una comunicación independiente de redes externas, ideal para pruebas, configuraciones locales o entornos sin infraestructura Wi-Fi disponible.


 ---
#### `variables.h` –  Inicialización del sistema de archivos SPIFFS

El archivo `variables.h` contiene todas las definiciones y declaraciones globales necesarias para el funcionamiento del sistema. Agrupa constantes relacionadas con la configuración de red (SSID, contraseñas), tiempos de operación, parámetros de los servomotores Dynamixel (como baudrate, protocolos, límites angulares, velocidades, direcciones de control, etc.), así como estructuras de datos que permiten almacenar trayectorias, configuraciones de servos y resultados de escaneo. También incluye banderas de control utilizadas por la máquina de estados principal y otras variables que permiten monitorear o ejecutar operaciones clave durante el ciclo del programa. Este archivo centraliza los recursos compartidos entre los diferentes módulos del sistema.




> Se recomienda mantener este archivo como una fuente única de definiciones globales, evitando duplicaciones en otros archivos. Toda variable global o estructura compartida entre módulos debe declararse aquí, siguiendo convenciones claras de nomenclatura y visibilidad. Esto facilita la mantenibilidad, la escalabilidad y el entendimiento del código a largo plazo.


 ---

### 3. ***Maquina de estados finitos (FSM)***:

El comportamiento del sistema embebido que corre en el ESP32 se basa en una **máquina de estados finitos (FSM, por sus siglas en inglés)**. Este enfoque estructurado permite controlar de forma secuencial las acciones del brazo robótico, garantizando que cada movimiento se complete correctamente antes de pasar al siguiente.

El uso de una FSM mejora la **robustez, mantenibilidad y control de flujo**, especialmente cuando se manejan secuencias de múltiples puntos, eventos asíncronos o condiciones de validación (como la detección de servos activos, límites de posición o errores de comunicación).

- Cada **estado** representa una etapa específica del proceso (por ejemplo: inactivo, moviendo, esperando confirmación, etc.).
- El sistema **avanza de un estado a otro** cuando se cumplen ciertas condiciones (por ejemplo: llegada a la posición deseada, timeout, respuesta del servo).
- Se utilizan **temporizadores, banderas de confirmación y buffers de trayectoria** para garantizar una ejecución segura y sincrónica.


![Maquina estados](/Docs/images/FSM.png) 



| Estado                  | Descripción                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| `inactivo`              | Estado inicial. Espera una acción del usuario, ya sea para mover un solo servo o iniciar una trayectoria. |
| `verificar Posición Actual` | El sistema consulta la posición real del servo para saber si ha alcanzado la posición objetivo.   |
| `Secuencia Iniciada`    | Entrada al modo de trayectoria. Establece el `ejecutandoSecuencia` para comenzar. |
| `Checar Servo`          | Determina si el servo actual está activo y tiene puntos válidos.           |
| `moverServo`            | Envía el comando al servo actual con su posición objetivo.                 |
| `Saltar Servo`          | Se ejecuta si el servo está inactivo o no tiene puntos almacenados.        |
| `Siguiente servo`       | Avanza al siguiente servo en la lista de ejecución.                        |
| `Siguiente punto`       | Pasa al siguiente punto de trayectoria si todos los servos han completado el anterior. |
| `Fin Trayectoria`       | Estado final del sistema automático, retorna al estado `inactivo`.         |
| `Limpiar trayectoria`   | Limpieza del buffer de trayectoria. Reinicia contadores.            |
| `Movimiento simple`     | Movimiento inmediato a una posición específica (fuera de trayectorias).Establece el `moveSimple` para comenzar.    |
| `Escaneo`     | Entrada al modo de escaneo. Establece el `scanMode` para comenzar.   |

---

#### Flujo:

1. El sistema comienza en el estado **inactivo**.
2. Si se activa la bandera `moveSimple`, se ejecuta un **movimiento inmediato** y se pasa por el estado `verificar Posición Actual` hasta que se alcanza la meta.
3. Si se activa la bandera `ejecutandoSecuencia`, se inicia una **secuencia de trayectoria**:
   - Se pasa a `Secuencia Iniciada`, luego a `Checar Servo`, donde se evalúa si el servo está activo.
   - Si el servo tiene puntos válidos, se pasa a `moverServo`, luego a `verificar Posición Actual`.
   - Si la posición se alcanzó, se evalúa si hay más servos (`currentServo < MAX_SERVOS`) o más puntos en la trayectoria (`maxPoints > currentPoint`).
   - De lo contrario, se finaliza en el estado `Fin Trayectoria`.
   - Como ultimo estado entra a `limpiar trayectoria`, la cual elimina los puntos de los Servos y sus contadores para volver a escribir una nueva trayectoria
4. Si se activa la bandera `scanMode`, se pasa por el estado `Escaneo` : 
   - Se ejecuta `scanServoDxl()` para detectar los servos conectados.
   - Los resultados se ordenan con `reorderScanDXL()` según el modelo esperado.
   - Se envía al cliente un JSON con los resultados usando `scanResultsJSON()`.
   - Para cada posición esperada (`MAX_SERVOS`):
     - Si hay un servo presente, se configura con `IndConfigDXL(i)` y se marca como activo.
     - Si no hay un servo, se marca como inactivo (`servoActivo[i] = false`).
     - En ambos casos, se envía al cliente el estado visual con `chanceIconJSON()`.
   - Finalmente, se desactiva la bandera `scanMode` para salir del estado.


---

#### Observaciones:

- El sistema permite un control **flexible y seguro**: cada transición ocurre solamente cuando se cumplen las condiciones específicas de posición, servo activo y punto alcanzado.
- La arquitectura soporta hasta `MAX_SERVOS` y múltiples puntos de trayectoria por servo (con un maximo de 10 puntos por servo), lo cual se valida dinámicamente.
- La lógica asegura que el **flujo se pueda interrumpir o reiniciar** en caso de eventos inesperados o entrada de nuevos comandos por parte del cliente.







---



### 4. ***Componentes***:
| Elemento                          | Función principal                                                                 |
|----------------------------------|------------------------------------------------------------------------------------|
| **Cliente (navegador web)**      | Dispositivo del usuario (PC, móvil, tablet) que accede al servidor vía Wi-Fi.     |
| **Servidor Web (ESP32)**         | Microcontrolador con Wi-Fi que aloja la interfaz gráfica en SPIFFS y gestiona comandos. |
| **Microcontrolador ESP32 - SPIFFS** | Parte embebida del ESP32 que contiene el sistema de archivos y ejecuta el firmware de control. |
| **DYNAMIXEL Shield MKR**         | Módulo intermediario que permite la comunicación UART half-duplex con los servos Dynamixel. |
| **Servomotores (MX106, XM430, AX-18A)** | Motores inteligentes conectados en cadena, cada uno con una función específica en el brazo robótico. |
| **Brazo robótico (4 GDL)**       | Mecanismo físico que recibe los movimientos solicitados y los ejecuta de forma coordinada. |

---

#### Flujo:

1. El usuario se conecta al **ESP32** vía Wi-Fi desde un navegador web.
2. La interfaz gráfica es servida desde la memoria SPIFFS del ESP32.
3. Al interactuar con la interfaz (por ejemplo, mover un servo), se envía una solicitud HTTP al ESP32.
4. El ESP32 interpreta la orden y se comunica con los servomotores a través del **DYNAMIXEL Shield MKR**, usando UART en modo half-duplex.
5. Los servomotores **ejecutan el movimiento solicitado** y, si es necesario, responden con su posición actual o estado.
6. La retroalimentación es enviada de vuelta al cliente y se visualiza en tiempo real en la interfaz web.

---

#### Observaciones:

- **Autonomía completa**: No requiere conexión a Internet.
- **Acceso multiplataforma**: Puede controlarse desde cualquier dispositivo con navegador.
- **Diseño modular**: Hardware y software están desacoplados, facilitando mantenimiento y expansión.
- **Comunicación eficiente**: UART half-duplex entre el ESP32 y los servos reduce el cableado y aumenta la confiabilidad.

---
IMAGEN

![Interacción Cliente-Servidor](/Docs/images/Servidor.png) 
#### Figura 5 – Interacción Cliente-Servidor

Este diagrama representa el proceso de comunicación entre la interfaz web del usuario, el microcontrolador ESP32 y el servomotor Dynamixel, durante una solicitud de movimiento. El flujo describe con claridad cómo se emite una orden, cómo se traduce en una acción física y cómo se devuelve una confirmación al cliente.

---

#### Componentes:

| Elemento       | Descripción breve                                                                 |
|----------------|------------------------------------------------------------------------------------|
| **Cliente**    | Interfaz web alojada en el navegador del usuario.                                 |
| **ESP32**      | Microcontrolador con firmware embebido, encargado de interpretar solicitudes.     |
| **Dynamixel**  | Servomotor inteligente controlado vía protocolo UART.                             |

---

#### Flujo:

1. **[Cliente → ESP32]**  
   El cliente genera una solicitud `GET` al ESP32 desde la interfaz web, utilizando la siguiente estructura de parámetros:
   ```
   /move?servo={ID}&type={tipoUnidad}&value={posición}
   ```
   - `servo`: número del servo (ej. 1, 2, 3, 4)
   - `type`: tipo de unidad (`angle`, `unit`, etc.)
   - `value`: valor deseado (ej. `180` grados o `2048` unidades)

2. **[ESP32 → Dynamixel]**  
   El ESP32 interpreta los parámetros y emite un comando `setGoalPosition(UART)` al servomotor Dynamixel. Esta orden establece la nueva posición deseada del actuador.

3. **[Dynamixel → ESP32]**  
   Tras ejecutar la instrucción, el servo responde con su posición actual. El ESP32 usa el comando `getPresentPosition(UART)` para obtener esta retroalimentación.

4. **[ESP32 → Cliente]**  
   Finalmente, el ESP32 envía una respuesta HTTP con estado `200 OK` al cliente, acompañada de un objeto JSON con los datos de confirmación del movimiento. Esta información puede utilizarse para actualizar íconos, mensajes o tablas en la interfaz.

---

#### Observaciones:

- El sistema utiliza **AJAX** (JavaScript asincrónico) para realizar esta interacción sin recargar la página, manteniendo la experiencia del usuario fluida y moderna.
- El protocolo **UART half-duplex** garantiza una comunicación eficiente entre el ESP32 y los servos Dynamixel.
- Esta secuencia es reutilizable para distintas funciones: **movimiento inmediato**, **agregar puntos de trayectoria**, **cambios de PID**, entre otros.

---
IMAGEN

![Arquitectura del servidor asincrono](/Docs/images/ServidorAsync.png) 
#### Figura 7 – Arquitectura del servidor asíncrono

Este diagrama ilustra la lógica interna del servidor embebido en el ESP32, el cual opera de manera **asíncrona** para manejar múltiples rutas y solicitudes sin bloquear la ejecución del programa principal. Refleja cómo se interpretan y procesan diferentes comandos provenientes del cliente web.

---

#### Componentes:

| Elemento             | Descripción                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| **Cliente**          | Usuario que realiza acciones desde la interfaz web                         |
| **Servidor ESP32**   | Firmware asíncrono que gestiona las rutas, peticiones y lógica de control  |
| **Trayectoria**      | Conjunto de puntos almacenados para cada servo                             |
| **Parámetros**       | Datos de configuración de servos: PID, velocidad, ID, baudrate, etc.        |

---

#### Flujo:

1. **Espera cliente / Nueva solicitud**
   - El servidor está en modo escucha, esperando conexiones entrantes.
   - Una vez recibida la solicitud, se evalúa la **ruta solicitada** (ej. `/move`, `/add`, `/start`).

2. **Procesamiento de rutas**  
   Dependiendo del endpoint solicitado, se activa un subproceso:

   ##### `/move`
   - Identifica el servo solicitado.
   - Envía un comando de movimiento inmediato (`Mover Servo`).

   ##### `/add`
   - Identifica el servo y almacena el punto recibido en la **trayectoria**.

   ##### `/start`
   - Accede a la trayectoria completa almacenada.
   - Ejecuta la secuencia de movimientos servo por servo, en orden.

   ##### `/servoParam`
   - Identifica el servo.
   - Sobrescribe los parámetros PID enviados.
   - Actualiza la estructura de **parámetros** global.

   ##### `/scan`
   - Inicia búsqueda de servos conectados.
   - Guarda la lista de dispositivos detectados en la estructura de **parámetros**.

   ##### `/moveParam`
   - Identifica el servo.
   - Sobrescribe velocidad y aceleración.

3. **Gestión de estructuras**
   - Los puntos de trayectoria se almacenan en un contenedor local (puede ser un array o estructura).
   - Los parámetros de cada servo se guardan para uso posterior y visualización en la interfaz.

4. **Respuesta**
   - Finalmente, el servidor prepara una respuesta al cliente web (`Mandar Info`), con mensajes de éxito, errores o estados actualizados.

---

#### Observaciones:

- Este flujo permite manejar múltiples tipos de solicitudes sin detener el sistema.
- El diseño modular facilita la extensión: se pueden añadir nuevas rutas fácilmente.
- La arquitectura es **escalable**, permitiendo la incorporación de más servos u otras funciones como sensores.
- Gracias al uso de **ESPAsyncWebServer**, las rutas no bloquean la ejecución principal del ESP32.

---

![Arquitectura modular del firmware](/Docs/images/ArchFirm.png) 
### Figura 8 – Arquitectura modular del firmware

La Figura 8 representa la estructura modular del firmware que corre sobre el ESP32, evidenciando la separación lógica de responsabilidades a través de archivos `.hpp` (cabeceras) bien definidos. Esta arquitectura facilita el mantenimiento, la escalabilidad y la depuración del sistema embebido, dividiendo claramente el manejo de red, interfaz web, comunicación con los servomotores y gestión de parámetros.

---