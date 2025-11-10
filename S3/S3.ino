#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqtt(client);

const String SSID = "FIESC_IOT_EDU";
const String PASS = "8120gv08";

<<<<<<< HEAD
const int PORT = 8883;
const String URL = "eba0a505da6c475ab42417c558e8c674.s1.eu.hivemq.cloud";

const String broker_user = "";
const String broker_pass = "";
=======
const int PORT = 1883;
const String URL = "test.mosquitto.org";
const String broker_user = ""; 
const String broker_pass = ""; 
const String MyTopic = "Topico_Bueno_123";
const String OtherTopic = "Topico_Monteiro_123";
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8

//meus tópicos
const String S3_presenca = "presenca ";
const String Servo1 = " Servo1 ";
const String Servo2 = " Servo2";

//outros tópicos
const String S2_P1 = "S2/P1";
const String S2_P2 = "S2/P2";
const String iluminacao = "iluminacao";
const String S3_presenca = "presenca";

void setup() {
<<<<<<< HEAD
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
=======
  pinMode(2 ,OUTPUT);
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8
  Serial.begin(115200);
  Serial.println("Conectando ao Wifi");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nConectado!");
  Serial.println("Conectando ao Broker...");
  mqtt.setServer(URL.c_str(), PORT);
<<<<<<< HEAD
  while (!mqtt.connected()) {
=======
  while(!mqtt.connected()){
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8
    String ID = "S1-";
    ID += String(random(0xffff), HEX);
    mqtt.connect(ID.c_str(), broker_user.c_str(), broker_pass.c_str());
    delay(200);
    Serial.print(".");
  }
<<<<<<< HEAD
  mqtt.subscribe(S2_P1.c_str());
  mqtt.subscribe(S2_P2.c_str());
  mqtt.subscribe(iluminacao.c_str());
  mqtt.subscribe(S3_presenca.c_str());
=======
  mqtt.subscribe(MyTopic.c_str());
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8
  mqtt.setCallback(callback);
  Serial.println("\n Conectado ao broker com sucesso!");
}

void loop() {
  String mensagem = "to de boa na lagoa";
<<<<<<< HEAD
  if (Serial.available() > 0) {
    mensagem += Serial.readStringUntil('\n');
    mqtt.publish(S3_presenca.c_str(), mensagem.c_str());
    mqtt.publish(Servo1.c_str(), mensagem.c_str());
    mqtt.publish(Servo2.c_str(), mensagem.c_str());
  }

  mqtt.loop();
  delay(2000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for (int i = 0; i < length; i++) {
=======
  if(Serial.available()>0){
    mensagem += Serial.readStringUntil('\n');
    mqtt.publish(OtherTopic.c_str(), mensagem.c_str());

  }

  mqtt.loop();
  delay(2000);

}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for(int i = 0; i < length; i++){
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8
    mensagem += (char)payload[i];
  }
  Serial.print("Recebidos: ");
  Serial.println(mensagem);
<<<<<<< HEAD

  if (topic == "iluminacao") {
    if (mensagem == "acender") {
      digitalWrite(2, HIGHT);
    }else{
      digitalWrite(2, LOW);
    }
  }

  if (topic == "S3_presenca") {
    if (mensagem == "acender") {
      digitalWrite(3, HIGHT);
    }else{
      digitalWrite(3, LOW);
    }
  }

  if (topic == "S2_P1") {
    if (mensagem == "acender") {
      digitalWrite(4, HIGHT);
    }else{
      digitalWrite(4, LOW);
    }
  }

  if (topic == "S2_P2") {
    if (mensagem == "acender") {
      digitalWrite(5, HIGHT);
    }else{
      digitalWrite(5, LOW);
    }
  }
}
=======
  if(mensagem == "marééé!!marééé!!"){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  
}
>>>>>>> b4e70b8ba8143078a5f995eb9c1a3d79c7eae8c8
