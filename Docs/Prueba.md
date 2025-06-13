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