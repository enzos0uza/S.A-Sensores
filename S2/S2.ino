#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);

const char* SSID = "FIESC_IOT_EDU";
const char* PASS = "8120gv08";

const int PORT = 8883;
const String URL = "eba0a505da6c475ab42417c558e8c674.s1.eu.hivemq.cloud";
const String broker_user = "sesi"; 
const String broker_pass = "SofiaForte"; 
const String iluminacaoTopic = "S1/iluminacao";
const String presencaTopic1 = "S2/presenca1";
const String presencaTopic2 = "S2/presenca2";

#define led 23
#define echoP1 18
#define echoP2 19

void setup() {
  pinMode(led, OUTPUT);
  pinMode(echoP1, INPUT);
  pinMode(echoP2, INPUT);
  Serial.begin(115200);
  Serial.println("Conectando ao Wifi");
  WiFi.begin(SSID, PASS);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nConectado!");
  Serial.println("Conectando ao Broker...");
  mqtt.setServer(URL.c_str(), PORT);
  while(!mqtt.connected()){
    String ID = "S1-";
    ID += String(random(0xffff), HEX);
    mqtt.connect(ID.c_str(), broker_user.c_str(), broker_pass.c_str());
    delay(200);
    Serial.print(".");
  }
  mqtt.subscribe(MyTopic.c_str());
  mqtt.setCallback(callback);
  Serial.println("\n Conectado ao broker com sucesso!");
}

void loop() {
 long duration1 = pulseIn(echoP1, HIGH);
  long duration2 = pulseIn(echoP2, HIGH);

  float distance1 = duration1 * 0.0343 / 2;
  float distance2 = duration2 * 0.0343 / 2;

  String mensagem1 = String(distance1);
  String mensagem2 = String(distance2);

  mqtt.publish(OtherTopic.c_str(), mensagem1.c_str());  
  mqtt.publish(OtherTopic.c_str(), mensagem2.c_str());  

  mqtt.loop();
  delay(2000);  

}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for(int i = 0; i < length; i++){
    mensagem += (char)payload[i];
  }
  Serial.print("Recebidos: ");
  Serial.println(mensagem);
if (String(topic) == iluminacaoTopic) {  
    float iluminacao = mensagem.toFloat();  
    if (iluminacao > 100) {
      digitalWrite(led, LOW); 
    } else {
      digitalWrite(led, HIGH); 
    }
  }
}