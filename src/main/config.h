const char *ssid = "MOVISTAR_3328";
const char *password = "Hy7H9C9PMV3wxz7K49z9";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char *hostname = "ESP8266.calderon";

// URL del servidor donde enviarás los datos
// const char* serverUrl = "http://SmartGarden.com/api/data";
const char *serverUrl = "http://192.168.1.42:5000/api/data";

typedef struct sensorMessage
{
  int air_temperature;
  int air_humidity;
  int luminosity;
  int soil_moisture_steel;
  int soil_moisture;
} SensorMessage;
