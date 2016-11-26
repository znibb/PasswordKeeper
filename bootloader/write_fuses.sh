#!/bin/bash

avrdude -c avrisp2 -p m32u4 -U lfuse:w:0xBE:m -U hfuse:w:0xD9:m -U efuse:w:0xC7:m
