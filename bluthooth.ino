#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
int received;
char receivedChar;
const int LEDpin = 2;
float data=25.98;
char charArray[10]; 


void setup() {
  Serial.begin(9600);
  SerialBT.begin("abinaya");
  Serial.println("The device started, now you can pair it with bluetooth!");
  //Serial.println("To turn ON send: a");
  //Serial.println("To turn OFF send: b"); 
  pinMode(LEDpin, OUTPUT);
 
}

void loop() {
    receivedChar =(char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  if (SerialBT.available()) {
    
    SerialBT.print("Received:");// write on BT app
    SerialBT.println(receivedChar);// write on BT app      
    Serial.print ("Received:");//print on serial monitor
    Serial.println(receivedChar);//print on serial monitor    
        if(receivedChar == '1')
    {
     SerialBT.println("LED ON:");// write on BT app
     Serial.println("LED ON:");//write on serial monitor
     digitalWrite(LEDpin, HIGH);// turn the LED ON
       
    }
    if(receivedChar == '0')
    {
     SerialBT.println("LED OFF:");// write on BT app
     Serial.println("LED OFF:");//write on serial monitor
      digitalWrite(LEDpin, LOW);// turn the LED off 
    }    
     else if(receivedChar == '3'){
      dtostrf(data, 6, 0, charArray); // float to char convertion 
      SerialBT.println(charArray);
      delay(100);      
    }
  }
  delay(20);
}
