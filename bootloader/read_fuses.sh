#!/bin/bash

avrdude -c avrisp2 -p m32u4 -U lfuse:r:low_fuse_val.txt:h -U hfuse:r:high_fuse_val.txt:h -U efuse:r:ext_fuse_val.txt:h

