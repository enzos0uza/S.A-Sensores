#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS = "8120gv08";

const int PORT = 1883;
const String URL = "test.mosquitto.org";
const String broker_user = ""; 
const String broker_pass = ""; 
//meus tópicos
const String S3_presenca = "presenca ";
const String Servo1 = " Servo1 ";
const String Servo2 = " Servo2";

//outros tópicos
const String S2_P1 = "S2/P1";
const String S2_P2 = "S2/P2";
const String iluminacao = "iluminacao";
const String S3_presenca = "presenca";

#define led 19
#define red 14  
#define green 18  
#define blue 17

#define echo 18

Servo servo1;
Servo servo2;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(echo, INPUT);
  servo1.attach(26); // Pino para servo 1
  servo2.attach(25); // Pino para servo 2

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
  mqtt.subscribe(S3_presenca.c_str());
  mqtt.subscribe(Servo1.c_str());
  mqtt.subscribe(Servo2.c_str());
  mqtt.setCallback(callback);
  Serial.println("\n Conectado ao broker com sucesso!");
}

void loop() {
  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.0343 / 2;
  float mensagem1 = String(distance); 
  if (mensagem1 == 2){
    mensagem2 = 90;
    servo1.write(mensagem2);
  }
  servo2.write(mensagem3);

  mqtt.publish(S3_presenca.c_str(), mensagem1.c_str());
  mqtt.publish(Servo1.c_str(), mensagem2.c_str());
  mqtt.publish(Servo2.c_str(), mensagem3.c_str());
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
if (topic == "iluminacao") {
    if (mensagem == "acender") {
      digitalWrite(led, HIGHT);
    }else{
      digitalWrite(led, LOW);
    }
  }

  if (topic == "S3_presenca") {
    if (mensagem == "acender") {
    servo2.write(90)
    }else{
    servo2.write(0)
    }
  }

  if (topic == "S2_P1") {
    if (mensagem <= 5>) {
      servo1.write(120)
    }else{
      servo1.write(0)
    }
  }

  if (topic == "S2_P2") {
    if (mensagem == "acender") {
    servo1.write(90)
    servo2.write(90)
  }else{
    servo1.write(0)
    servo2.write(0)
  }
}
}
