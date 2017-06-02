/*
  TagData.cpp - Library for storing UID/password pairs for use with PasswordKeeper.
  Created by znibb, June 1, 2017.
*/

#include <Arduino.h>
#include "TagData.h"

TagData::TagData(){};

TagData::TagData(byte nbr_of_tags, byte uid_size, byte pwd_size){
  _nbr_of_tags = nbr_of_tags;
  _uid_size = uid_size;
  _pwd_size = pwd_size;

  tags = (Tag *)malloc(sizeof(Tag) * nbr_of_tags);

  for(int i = 0; i < _nbr_of_tags; i++){
    tags[i] = Tag(_uid_size, _pwd_size);
  }
}

char TagData::getIndexOf(byte *requested_uid, byte req_size){
  byte uid[_uid_size];
  for(char i = 0; i < _nbr_of_tags; i++){
    tags[i].getUid(uid);

    #ifdef DEBUG
    Serial.print("Comparing tag ");
    Serial.println(i+1, DEC);
    #endif

    if(_checkPair(requested_uid, req_size, uid, _uid_size) == true){
      return i;
    }
  }

  // Return -1 to indicate requested_uid is not in the list
  return -1;
}

// Check if two byte arrays match
// Will return true if the first 'a_size' elements in 'a' and 'b' are the same even if a is a shorter array than b
bool TagData::_checkPair(byte a[], byte a_size, byte b[], byte b_size){
  #ifdef DEBUG
  // Printout both arrays to Serial
  for(int i = 0; i < a_size; i++){
    Serial.print(a[i] < 0x10 ? " 0" : " ");
    Serial.print(a[i], HEX);
  }
  Serial.println();
  for(int i = 0; i < b_size; i++){
    Serial.print(b[i] < 0x10 ? " 0" : " ");
    Serial.print(b[i], HEX);
  }
  Serial.println();
  #endif

  // Compare arrays element by element
  bool match = true;
  for(byte i = 0; i < a_size; i++){
    if(a[i] != b[i]){
      match = false;
    }
  }
  // Return result
  if(match){
    return true;
  }
  else{
    return false;
  }
}
