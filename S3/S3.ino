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
const String MyTopic = "Topico_Bueno_123";
const String OtherTopic = "Topico_Monteiro_123";

void setup() {
  pinMode(2 ,OUTPUT);
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
  String mensagem = "to de boa na lagoa";
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
    mensagem += (char)payload[i];
  }
  Serial.print("Recebidos: ");
  Serial.println(mensagem);
  if(mensagem == "marééé!!marééé!!"){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  
}
