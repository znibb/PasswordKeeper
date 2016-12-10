#include <Arduino.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define RST_PIN 4
#define SS_PIN 11
#define ACT_LED_PIN 5
#define TAG_LED_PIN 13
#define BUTTON_PIN "PE2"

const int blinkDelay = 500;
const int authDelay = 2000;
const int tagDelay = 1000;
const int loopDelay = 1000;
const byte masterUID[] = {0xFF, 0xFF, 0xFF, 0xFF};
const char password[] = "SUPER SECRET PASSWORD\n";

unsigned long actExpirationTime;
unsigned long tagExpirationTime;

MFRC522 rfid(SS_PIN, RST_PIN);

boolean buttonState(String);
boolean checkPair(const byte[], byte[]);
void enableLed(byte, const int);
void flashLeds(byte);
void ledHandler(void);

void setup(){
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);

  pinMode(ACT_LED_PIN, OUTPUT);
  pinMode(TAG_LED_PIN, OUTPUT);
  DDRE &= B11111011;  // Set PE2 as input

  flashLeds(2);
}

void loop(){
  ledHandler();

  if(buttonState(BUTTON_PIN)){
    enableLed(TAG_LED_PIN, tagDelay);
  }

  if(!rfid.PICC_IsNewCardPresent()){
    return;
  }
  if(!rfid.PICC_ReadCardSerial()){
    return;
  }

  enableLed(TAG_LED_PIN, tagDelay);

  byte readUID[rfid.uid.size];
  Serial.print("Read Card UID:");
  for(byte i = 0; i < rfid.uid.size; i++){
    readUID[i] = rfid.uid.uidByte[i];
    Serial.print(readUID[i] < 0x10 ? " 0" : " ");
    Serial.print(readUID[i], HEX);
  }
  Serial.println();

  if(checkPair(masterUID, readUID)){
    Serial.println("Authorized");
    Keyboard.print(password);
    enableLed(ACT_LED_PIN, authDelay);
  }
  else{
    Serial.println("Unauthorized");
  }

  delay(loopDelay);
}

boolean buttonState(String button){
  if(button.compareTo(BUTTON_PIN) == 0){
    if((PINE & B00000100) == 0){
      Serial.println("Button pressed");
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
boolean checkPair(const byte a[], byte b[]){
  boolean match = true;
  for(byte i = 0; i < rfid.uid.size; i++){
    if(a[i] != b[i]){
      match = false;
    }
  }
  if(match){
    return true;
  }
  else{
    return false;
  }
}
void enableLed(byte led, const int duration){
  if(led == ACT_LED_PIN){
    actExpirationTime = millis() + duration;
    digitalWrite(ACT_LED_PIN, HIGH);
  }
  else if(led == TAG_LED_PIN){
    tagExpirationTime = millis() + duration;
    digitalWrite(TAG_LED_PIN, HIGH);
  }
}
void flashLeds(byte count){
  for(byte i = 0; i < count; i++){
    digitalWrite(ACT_LED_PIN, HIGH);
    digitalWrite(TAG_LED_PIN, LOW);
    delay(blinkDelay);
    digitalWrite(ACT_LED_PIN, LOW);
    digitalWrite(TAG_LED_PIN, HIGH);
    delay(blinkDelay);
  }
  digitalWrite(ACT_LED_PIN, LOW);
  digitalWrite(TAG_LED_PIN, LOW);
}
void ledHandler(){
  unsigned long currentTime = millis();
  if(digitalRead(ACT_LED_PIN) && currentTime >= actExpirationTime){
    digitalWrite(ACT_LED_PIN, LOW);
  }
  if(digitalRead(TAG_LED_PIN) && currentTime >= tagExpirationTime){
    digitalWrite(TAG_LED_PIN, LOW);
  }
}
