int smssend=1;  

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() {
  
  Serial.begin(19200);  //Скорость порта для связи Arduino с компьютером
  Serial.println("Goodnight moon!");
  mySerial.begin(19200);  //Скорость порта для связи Arduino с GSM модулем
  //mySerial.println("ATD+79037404216;");
  mySerial.println("ATI");
  mySerial.println("AT+CMGF=1");
}

void loop() {
  
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}


void sms(String text, String phone) {
  Serial.println("SMS send started");
  mySerial.println("AT+CMGS=\"" + phone + "\"");
  delay(1000);
  mySerial.print(text);
  delay(300);
  mySerial.print((char)26);
  delay(300);
  Serial.println("SMS send finish");
  delay(3000);
}
