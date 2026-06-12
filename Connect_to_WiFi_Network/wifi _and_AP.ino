#include <ESP8266WiFi.h>

const char* ssid = ".";
const char* password = "987654321";

WiFiClient client;
WiFiServer server(80);

#define led D5

IPAddress local_IP(192,168,10,1);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255,255,255,0);


// void setup() 
// {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   WiFi.softAPConfig(local_IP, gateway, subnet);
//   WiFi.softAP("Home-automation", "123456789");
//   Serial.println();
//   Serial.println("NodeMCU Started!");
//   Serial.println(WiFi.softAPIP());
//   server.begin();
//   pinMode(led, OUTPUT);
// }

void setup() {
  Serial.begin(9600);
  // AP + Station Mode
  WiFi.mode(WIFI_AP_STA);
  // Connect to Router
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to Router");
  Serial.print("Router IP: ");
  Serial.println(WiFi.localIP());

  // Create Access Point
  WiFi.softAPConfig(local_IP, gateway, subnet);

  WiFi.softAP(
    "Home-automation",
    "123456789"
  );
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(led, OUTPUT);
}
void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
  }
}
