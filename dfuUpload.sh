#!/bin/sh
DEVICE_NAME=atmega32u4
HEX_PATH=.pioenvs/leonardo/firmware.hex

lsusb | grep 'atmega32u4 DFU bootloader' > /dev/null
if [ $? -eq 0 ]; then
  dfu-programmer $DEVICE_NAME erase
  dfu-programmer $DEVICE_NAME flash $HEX_PATH
  dfu-programmer $DEVICE_NAME start
  echo "Upload complete"
  exit 0
else
  echo "Connection error, no target detected"
  exit 1
fi
