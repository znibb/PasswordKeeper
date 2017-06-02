/*
  Tag.h - Class representing a UID/password pair for use with TagData
  Created by znibb, June 1, 2017.
*/

#ifndef Tag_h
#define Tag_h

#include <Arduino.h>

class Tag{
public:
  Tag();
  Tag(byte uid_size, byte pwd_size);
  void setUid(byte *uid);
  void setPwd(char *pwd);
  void getUid(byte *uid);
  void getPwd(char *pwd);

private:
  byte _uid_size;
  byte _pwd_size;
  byte *_uid;
  char *_pwd;
};

#endif
