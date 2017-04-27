# Bootloader tools
* Software
  - Blink.hex
    - Compiled standard Blink sketch.
  - Blink_with_bl.hex
    - Same as above but also contains the bootloader section.
  - Caterina-Leonardo.hex
    - Standard Arduino Leonardo bootloader.
* Scripts
  - dfuUpload.sh
    - Flash software over USB to a MCU in DFU mode.
  - load_bootloader.sh
    - Burn bootloader using avrdude and a AVRISP2 programmer.
  - read_fuses.sh
    - Read out fuse values using avrdude and a AVRISP2 programmer. Stores the values in separate txt files.
  - write_fuses.sh
    - Set fuse values to suitable values, described in 'fuses.txt'
* Information
  - fuses.txt
    - Explains the used fuse values
