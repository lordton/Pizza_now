const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  12;      // the number of the LED pin
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW; 
int smssend=1;  
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(12, OUTPUT); 
pinMode(13, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);

  // set initial LED state

 digitalWrite(10, HIGH); 
delay(10000); // wait until gsm module boots up
  
  Serial.begin(19200);  //Скорость порта для связи Arduino с компьютером
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  mySerial.begin(19200);  //Скорость порта для связи Arduino с GSM модулем
  //mySerial.println("ATD+79037404216;");
  //mySerial.println("ATI");
  mySerial.println("AT+CMGF=1");

  digitalWrite(10, LOW); 
}

void loop() {

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {

        
            digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
          // wait for a second
 // turn the LED off by making the voltage LOW

   // wait for a second

  
        mySerial.println("ATI");
        sms("little meow meow","89263637230");

          digitalWrite(10, LOW);   
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
  
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


  



