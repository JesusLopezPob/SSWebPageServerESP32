// =========================
//WiFi
// =========================
#define ssid "ESP32-AP"
#define pass "123456789"


// =========================
//Tiempo
// =========================
uint32_t t_anterior = 0;
uint32_t t_sensado = 1000;

#define TIMEOUT 1000


// =========================
// Configuración Dynamixel
// =========================

//UART

#define RX_PIN 16
#define TX_PIN 17
#define DXL_DIR_PIN 5

HardwareSerial& DXL_SERIAL = Serial2;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

//Parametros de los servos
uint8_t SERVO_IDS[] = { 4, 1, 2, 3};
int DXL_Baud = 1000000;



// config Servos Protocolo 2.0 (Servo 2 y 3)
const int NUM_SERVOS = sizeof(SERVO_IDS) ;
const float PROTOCOL_VERSION_2 = 2.0;
const int MAX_UNIT_2 = 4095;
const int MAX_ANGLE_2 = 360;

// config Servo 4 Protocolo 1.0
const float PROTOCOL_VERSION_1 = 1.0;


//============ AX18 ====================================//

// Direcciones para Protocolo 1.0 AX-18
#define AX_TORQUE_ENABLE_ADDR      24
#define AX_CW_ANGLE_LIMIT_ADDR     6
#define AX_CCW_ANGLE_LIMIT_ADDR    8
#define AX_GOAL_POSITION_ADDR      30
#define AX_LED_ADDR                25
#define AX_MOVING_SPEED_ADDR       32

#define AX_TORQUE_ENABLE_ADDR_LEN  1
#define AX_ANGLE_LIMIT_ADDR_LEN    2
#define AX_GOAL_POSITION_ADDR_LEN  2
#define AX_LED_ADDR_LEN            1
#define AX_MOVING_SPEED_ADDR_LEN   2

// Nueva definición para leer la posición actual en Protocolo 1.0 AX18
#define PRESENT_POSITION_ADDR     36
#define PRESENT_POSITION_ADDR_LEN  2

// Configuración Servo 3
uint16_t AX_CW_limit = 300;
uint16_t AX_CCW_limit = 500;
//uint16_t AX_speed = 50;

const int MAX_UNIT_1 = 1023;
const int MAX_ANGLE_1 = 300;

// Constantes para torque
const uint8_t TURN_ON  = 1;
const uint8_t TURN_OFF = 0;

// Tiempo de espera para las operaciones (ms)
#define TIMEOUT 1000


/*
//============ MX106 ====================================//

// Direcciones para Protocolo 2.0 MX-106
#define MX_TORQUE_ENABLE_ADDR      64
#define MX_MIN_POSITION_LIMIT      52
#define MX_MAX_POSITION_LIMIT      48
#define MX_GOAL_POSITION_ADDR      116
#define MX_LED_ADDR                65
#define MX_MOVING_SPEED_ADDR       104

#define MX_TORQUE_ENABLE_ADDR_LEN  1
#define MX_POSITION_LIMIT_LEN      4
#define MX_GOAL_POSITION_ADDR_LEN  4
#define MX_LED_ADDR_LEN            1
#define MX_MOVING_SPEED_ADDR_LEN   4

// Nueva definición para leer la posición actual en Protocolo 2.0 MX106
#define PRESENT_POSITION_ADDR      132
#define PRESENT_POSITION_ADDR_LEN  4
*/


// Configuración Servo 1 
uint16_t MX_speed = 50;
/*
uint16_t MX_CW_limit = 300;
uint16_t MX_CCW_limit = 500;

*/

//============ Scan ====================================//
//variables para el escaneo
#define MAX_SERVOS 4
int found_ids[MAX_SERVOS];
int max_servos = MAX_SERVOS;

struct ServoInfo {
  int id;
  int protocol;
  int baudrate;
  int model_number;
};

  ServoInfo scanDXL[4];

//estructuras de datos

//============ Servos  ====================================//
struct Punto {
    float valorPosicion;   // Valor de la posición (puede ser un número o ángulo)
    String tipo;           // Tipo: "unit" o "angle"
};

struct ServoConfig {
    int id;               // ID del servo
    int baudrate;         // Baudrate
    float protocolo;     // Protocolo de comunicación (por ejemplo, "1.0 o 2.0")
    float P, I, D;        // Parámetros PID
    int V, A;             // Velocidad y aceleración
    Punto puntos[10];     // Array para almacenar hasta 10 puntos
    int contadorPuntos;   // Número actual de puntos guardados
};

  ServoConfig servos[4];

//




// =========================
//Sensores Finales de carrera
// =========================
