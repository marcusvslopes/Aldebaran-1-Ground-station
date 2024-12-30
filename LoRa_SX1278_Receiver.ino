// LORA code for Receiver

#include <SPI.h>
#include <LoRa.h>

#define DIO0 26
#define SS   5
#define RESET 25
#define LED 2

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");

  configuraLoRa();
}


void configuraLoRa()
{
  // SPI.begin(/*sck*/ 18, /*miso*/ 19, /*mosi*/ 23, /*ss*/ 5);
  LoRa.setPins(SS, RESET, DIO0);
  if ( !LoRa.begin(401E6) ) {
    Serial.println("LoRa falhou!");
    while (1);
  }
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(4);
  LoRa.disableCrc();
  Serial.println("Iniciado.");
}


void loop() {
  digitalWrite(LED, LOW);
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    onReceive(packetSize);
  }
  delay(10);
}


void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");
  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print(LoRa.read(),HEX);
    Serial.print(' ');
  }
  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
  digitalWrite(LED, HIGH);
  Serial.println("Received  ");
  Serial.println(packetSize);
}
