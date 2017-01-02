# PasswordKeeper
Ever gotten tired manually inputing your password everytime you unlock your desktop? PasswordKeeper let's you use a RFID/NFC tag to input a password into your computer!
## About

The device consists of a custom designed circuit that uses an Atmega32u4 MCU to interface a MFRC522 contactless reader to any computer by emulating a keyboard over a USB connection, no driver or external software required!

The device stores a list of tags with an assoiciated password in the EEPROM of the MCU. When a user scans a tag the program returns the corresponding password as emulated keyboard presses. The sketch used to store user credentials in EEPROM can be found here: https://github.com/znibb/PasswordKeeper_loadData/.

## Usage
### Store user credentials
1. Download the loadData sketch from: https://github.com/znibb/PasswordKeeper_loadData/.
2. Edit loadData sketch with appropriate user credentials.
3. Upload loadData sketch.
4. Open a serial connection to the device to initialize the writing to EEPROM and to get feedback on the results.
5. Done.

### Prepare for operation
1. Clone/download the sketch from this repository.
2. Upload sketch.
3. Ready for use!

## Tips & tricks
- Don't know the UID of your tag? 
  - Upload the sketch and start a serial monitor. The sketch will output the UID of any scanned tag on the serial bus.
