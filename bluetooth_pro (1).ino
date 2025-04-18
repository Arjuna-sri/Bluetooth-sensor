#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int received;
char receivedChar;
const int LEDpin = 2;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("abinaya");
  Serial.println("The device started, now you can pair it with Bluetooth!");
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  receivedChar = (char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    SerialBT.print("Received: ");
    SerialBT.println(receivedChar); 
    Serial.print("Received: "); 
    Serial.println(receivedChar); 

    if (receivedChar == '1') {
      SerialBT.println("LED ON "); 
      Serial.println("LED ON: "); 
      digitalWrite(LEDpin, HIGH); 
    } 
    else if (receivedChar == '0') {
      SerialBT.println("LED OFF "); 
      Serial.println("LED OFF: "); 
      digitalWrite(LEDpin, LOW); 
    } 
    else if (receivedChar == '3') {
      for (int i = 0; i < 5; i++) { 
        SerialBT.println("LED ON ");
        digitalWrite(LEDpin, HIGH); 
        delay(1000); 
        SerialBT.println("LED OFF ");
        digitalWrite(LEDpin, LOW); 
        delay(1000); 
      }
    }
  }
  delay(20);
}
