// inclusão de bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>
//conexão com broker
WiFiClient client;
PubSubClient mqtt(client);

const char* SSID = "FIESC_IOT_EDU";
const char* PASS = "8120gv08";

const int PORT = 8883;
const String URL = "eba0a505da6c475ab42417c558e8c674.s1.eu.hivemq.cloud";
const String broker_user = "sesi"; 
const String broker_pass = "SofiaForte"; 

//definir topics
const String temperatura = "sensorTemp";
const String umidade = "sensorUmid";
const String iluminacao = "sensorIlu";
const String S1_presenca = "sensorUmidpic";

//outros topics
const String S1_iluminacao = "topic";

#define led 23
//sensores
#define echo1 18

#define LDR 34
#define DHT 35
//ledRGB
#define red 12
#define green 13
#define blue 14

void setup() {

  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(echo1, INPUT);
  pinMode(LDR, INPUT);
  pinMode(DHT, INPUT);

  //envio dos topicos paa o server
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
  //meus topicos
  mqtt.subscribe(temperatura.c_str());
  mqtt.subscribe(umidade.c_str());
  mqtt.subscribe(iluminacao.c_str());
  mqtt.subscribe(S1_presenca.c_str());
  mqtt.setCallback(callback);
  Serial.println("\n Conectado ao broker com sucesso!");
}

void loop() {
  //pegar dados dos sensores
  long duration = pulseIn(echo1, HIGH);
  float distance = duration * 0.0343 / 2;

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  int iluminacao = analogRead(LDR);


  String mensagem1 = String(distance);
  String mensagem2 = String(umidade);
  String mensagem3 = String(iluminacao);
  String mensagem4 = String(temperatura);
 
  //enviar topicos
  mqtt.publish(S1_presenca.c_str(), mensagem1.c_str());  
  mqtt.publish(umidade.c_str(), mensagem2.c_str()); 
  mqtt.publish(iluminacao.c_str(), mensagem3.c_str());  
  mqtt.publish(temperatura.c_str(), mensagem4.c_str());   

  mqtt.loop();
  delay(2000);  
}
//receber topicos
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