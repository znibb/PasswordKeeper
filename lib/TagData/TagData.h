/*
  TagData.h - Library for storing UID/password pairs for use with PasswordKeeper.
  Created by znibb, June 1, 2017.
*/

#ifndef TagData_h
#define TagData_h

#include <Arduino.h>
#include "Tag.h"

class TagData{
public:
  TagData();
  TagData(byte nbr_of_tags, byte uid_size, byte pwd_size);
  char getIndexOf(byte *uid, byte size);
  Tag *tags;

private:
  bool _checkPair(byte a[], byte a_size, byte b[], byte b_size);
  byte _nbr_of_tags;
  byte _uid_size;
  byte _pwd_size;
};

#endif
