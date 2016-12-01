#!/bin/bash

avrdude -c avrisp2 -p m32u4 -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xF0:m -U lock:w:0xEF:m
