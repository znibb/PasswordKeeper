#include <Arduino.h>
#include <EEPROM.h>
#include <Keyboard.h>
#include <MFRC522.h>

// Pin definitions
#define RST_PIN 4
#define SS_PIN 11
#define ACT_LED_PIN 5
#define TAG_LED_PIN 13
#define BUTTON_PIN "PE2"

// Parameters
const int blinkDelay = 500;
const int authDelay = 2000;
const int tagDelay = 1000;
const int loopDelay = 1000;
const int tagsSize = 10;

// Variables
unsigned long actExpirationTime;
unsigned long tagExpirationTime;

// Create variables for storing loaded user info
struct tagData{
  byte uid[7];
  char password[30];
};
struct tagData tags[tagsSize];
byte nbrOfTags;

// Initialize RFID reader object
MFRC522 rfid(SS_PIN, RST_PIN);

// Function prototypes
boolean buttonState(String);
boolean checkPair(byte[], byte[]);
void enableLed(byte, const int);
void flashLeds(byte);
void ledHandler(void);

void setup(){
  // Init serial port
  Serial.begin(115200);

  // Init RFID reader
  SPI.begin();
  rfid.PCD_Init();

  // Adjust RFID reader antenna gain
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);

  // Set pin modes
  pinMode(ACT_LED_PIN, OUTPUT);
  pinMode(TAG_LED_PIN, OUTPUT);
  DDRE &= B11111011;  // Set PE2 as input

  // Load user data from EEPROM
  int memAddr = 0;
  EEPROM.get(memAddr, nbrOfTags);
  if(nbrOfTags > tagsSize){
    Serial.print("Number of loaded entries (");
    Serial.print(nbrOfTags);
    Serial.print(") exceeds size of 'tags' container (");
    Serial.print(tagsSize);
    Serial.println("). Increase size!");
    return;
  }
  else{
    memAddr += sizeof(nbrOfTags);
    EEPROM.get(memAddr, tags);
    Serial.print("Loaded ");
    Serial.print(nbrOfTags);
    Serial.println(" tags.");
  }

  // Flash leds to indicate end of setup
  flashLeds(2);
}

void loop(){
  // Run subroutine to check of any LEDs should be turned off
  ledHandler();

  // Check for button press
  if(buttonState(BUTTON_PIN)){
    enableLed(TAG_LED_PIN, tagDelay);
  }

  // Check if a new tag is detected and return if none are found
  if(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
    return;
  }

  // Blink TAG LED once to show that a tag has been read
  enableLed(TAG_LED_PIN, tagDelay);

  // Read tag uid
  byte readUID[rfid.uid.size];
  Serial.print("Read Card UID:");
  for(byte i = 0; i < rfid.uid.size; i++){
    readUID[i] = rfid.uid.uidByte[i];
    Serial.print(readUID[i] < 0x10 ? " 0" : " ");
    Serial.print(readUID[i], HEX);
  }
  Serial.println();

  // Check if read uid matches any of the known tags
  bool match = false;
  byte index;
  for(byte i = 0; i < nbrOfTags; i++){
    if(checkPair(tags[i].uid, readUID)){
      match = true;
      index = i;
    }
  }

  // If tag is known output the corresponding password and blink ACT LED
  if(match){
    Serial.println("Authorized");
    Keyboard.print(tags[index].password);
    enableLed(ACT_LED_PIN, authDelay);
  }
  else{
    Serial.println("Unauthorized");
  }

  // Delay loop execution to prevent tag from being read multiple times in succession
  delay(loopDelay);
}

// Return button state using direct port manipulation
boolean buttonState(String button){
  // Desired input port specified as String
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

// Compare two byte arrays
boolean checkPair(byte a[], byte b[]){
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

// Enables a LED and stores the planned time for turn off (to be used by ledHandler)
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

// Alternate flashing LEDs with a specified amount of cycles
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

// Check if any of the LEDs have passed their duration and should be turned off
void ledHandler(){
  unsigned long currentTime = millis();
  if(digitalRead(ACT_LED_PIN) && currentTime >= actExpirationTime){
    digitalWrite(ACT_LED_PIN, LOW);
  }
  if(digitalRead(TAG_LED_PIN) && currentTime >= tagExpirationTime){
    digitalWrite(TAG_LED_PIN, LOW);
  }
}
