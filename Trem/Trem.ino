#include <WiFi.h>
#include <PubSubClient.h>


const char* SSID = "FIESC_IOT_EDU";
const char* PASS = "8120gv08";

const int PORT = 1883;
const String URL = "test.mosquitto.org";
const String broker_user = ""; 
const String broker_pass = ""; 


const String MyTopic = "Velocidade";


const int LED_VERDE = 21;
const int LED_VERMELHO = 18;


WiFiClient client;
PubSubClient mqtt(client);



void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";

  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  Serial.print("Recebido no tópico ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(mensagem);

 
  int valor = mensagem.toInt();


  if (valor > 0) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  }
  else if (valor < 0) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }
  else {  
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
  }
}



void setup() {
  Serial.begin(115200);


  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");


  mqtt.setServer(URL.c_str(), PORT);
  mqtt.setCallback(callback);

  Serial.println("Conectando ao broker MQTT...");
  
  while (!mqtt.connected()) {
    String ID = "ESP32-";
    ID += String(random(0xffff), HEX);

    if (mqtt.connect(ID.c_str(), broker_user.c_str(), broker_pass.c_str())) {
      Serial.println("Conectado ao broker!");
    } else {
      Serial.print("Falha, rc=");
      Serial.println(mqtt.state());
      delay(1000);
    }
  }

  mqtt.subscribe(MyTopic.c_str());
  Serial.println("Inscrito no tópico: " + MyTopic);
}


void loop() {
  mqtt.loop();
}