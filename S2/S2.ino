#include <Wifi.h>
const String SSID = "nomeDaRede";
const String PASS = "senhaDaRede";
void setup() {
  Serial.begin(115200);
  Serial.println("Conectando ao WiFi");
  WiFi.begin(SSID, PASS);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConectado");
}

void loop() {

}
