#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT20.h>

DHT20 DHT;

const char* ssid = "SETUP-C4AD";
const char* pass = "advice7403again";
const char* server = "http://3.145.182.172:5000";  // Flask server on port 5000

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Wire.begin();
  DHT.begin();

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    DHT.read();
    float temperature = DHT.getTemperature();
    float humidity = DHT.getHumidity();

    
    String requestURL = String(server) + "/?t=" + String(temperature, 2) + "&h=" + String(humidity, 2);
    Serial.println("Requesting: " + requestURL);

    WiFiClient client;
    HTTPClient http;
    http.begin(client, requestURL);  // Using WiFiClient to specify a custom port

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Server response: ");
      Serial.println(http.getString());
    } else {
      Serial.print("Error in request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  else{
    Serial.println("Connection Lost");
  }

  delay(5000);
}
