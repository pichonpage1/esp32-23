//1. Inicializa la conexión WiFi y el sensor DHT11.
//2. Espera a que se establezca una conexión WiFi.
//3. En el bucle principal, lee los valores de temperatura y humedad del sensor DHT11.
//4. Realiza una solicitud HTTP GET a un servidor web, incluyendo los valores de temperatura y humedad como parámetros en la URL de la solicitud.
//5. Si la solicitud HTTP GET se completa con éxito, muestra la respuesta del servidor en el monitor serie.
//6. Si la solicitud HTTP GET falla, muestra un mensaje de error en el monitor serie.
//En resumen, el código lee los valores de temperatura y humedad de un sensor y los envía a un servidor web a través de una solicitud HTTP GET.
//La pagina web que muestra los datos(climalive.html) se aloja en la misma carpeta que 'actualizar.php' y  'datos.json', esta seria la ubicacion de los archivos en mi caso C:\xampp\htdocs\servidoriot2.
  


#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2          // Pin del sensor DHT11
#define DHTTYPE DHT11     // Tipo de sensor DHT11
#define WIFI_SSID "infinitum666"      // Nombre de la red WiFi
#define WIFI_PASSWORD "eldiabloandasuelto"  // Contraseña de la red WiFi

DHT dht(DHTPIN, DHTTYPE);
WiFiClient wifiClient;

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado a la red WiFi. Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000); // Esperar 5 segundos entre lecturas
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error al leer el sensor DHT11!");
    return;
  }
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C, Humedad: ");
  Serial.print(humidity);
  Serial.println("%");

  HTTPClient http;
  String url = "http://192.168.0.77/servidoriot2/actualizar.php?temp=" + String(temperature) + "&hum=" + String(humidity); // url donde esta guardado el archivo actualizar.php
  Serial.println(url);
  http.begin(wifiClient, url);
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.print("Error al enviar los datos al servidor. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
