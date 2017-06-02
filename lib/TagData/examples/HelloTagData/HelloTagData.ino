#include <Arduino.h>
#include "TagData.h"

const byte nbrOfTags = 2;
const byte uid_size = 4;
const byte pwd_size = 20;

byte tags_uid[nbrOfTags][uid_size] = {{0xFF, 0x4, 0xFD, 0xFC},
                                      {0x1,  0x2, 0x3,  0x4}};
char tags_pwd[nbrOfTags][pwd_size] = {"hello world",
                                      "testing testing"};

TagData tagData;

void setup(){
  Serial.begin(9600);
  while(!Serial);

  tagData = TagData(nbrOfTags, uid_size, pwd_size);

  // Write data to object
  for(int i = 0; i < nbrOfTags; i++){
    tagData.tags[i].setUid(tags_uid[i]);
    tagData.tags[i].setPwd(tags_pwd[i]);
  }

  // Read and printout data from object
  byte uid[uid_size];
  char pwd[pwd_size];

  for(int i = 0; i < nbrOfTags; i++){
    tagData.tags[i].getUid(uid);
    for(int j = 0; j < uid_size; j++){
      Serial.print(uid[j] < 0x10 ? " 0" : " ");
      Serial.print(uid[j], HEX);
    }
    Serial.println();

    tagData.tags[i].getPwd(pwd);
    Serial.println(pwd);
  }
  Serial.println();
}

void loop(){

}
