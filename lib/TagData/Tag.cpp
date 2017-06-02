/*
  Tag.cpp - Class representing a UID/password pair for use with TagData
  Created by znibb, June 1, 2017.
*/

#include <Arduino.h>
#include "Tag.h"

// Default constructor
Tag::Tag(){}

// Constructor with init
Tag::Tag(byte uid_size, byte pwd_size){
  _uid_size = uid_size;
  _pwd_size = pwd_size;

  _uid = (byte *)malloc(sizeof(byte) * _uid_size);
  _pwd = (char *)malloc(sizeof(char) * _pwd_size);
}

// Store uid
void Tag::setUid(byte *uid){
  memcpy(_uid, uid, _uid_size);
}

// Store password
void Tag::setPwd(char *pwd){
  memcpy(_pwd, pwd, _pwd_size);
}

// Return uid to supplied array
void Tag::getUid(byte *uid){
  memcpy(uid, _uid, _uid_size);
}

// Return password to supplied array
void Tag::getPwd(char *pwd){
  memcpy(pwd, _pwd, _pwd_size);
}
