# 📚 Documentación del Proyecto  

**Nombre del Proyecto**: Servidor Web ESP32  
**Descripción**: Sistema de control remoto para brazo robotico basado en servidor web embebido en una ESP32 

---
**Índice rápido**  
- [🚀 Instalación](#🚀-instalación)  
- [📋 Procedimiento inicialización](#📋-procedimiento-inicialización)  
  - [1. Alimentación del circuito](#1-alimentación-del-circuito-y-shield-dxl)  
  - [2. Conexión de servomotores](#2-conexión-de-servomotores-dynamixel)  
  - [3. 📶 Conexión vía Wi-Fi al dispositivo ESP32-AP](#3-📶-conexión-vía-wi-fi-al-dispositivo-esp32-ap)
  - [4. 🌐 Acceso a la interfaz web](#4-🌐-acceso-a-la-interfaz-web-del-ESP32)  
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




### 3. **📶 Conexión vía Wi-Fi al dispositivo ESP32-AP**
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



### 4. 🌐 **Acceso a la interfaz web del ESP32**

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


