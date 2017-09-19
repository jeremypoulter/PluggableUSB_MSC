#ifndef _CONFIG_H
#define _CONFIG_H

#define MAX_LUNS 1

// needs to be more than ~4200 (to force FAT16)
#define NUM_FAT_BLOCKS 8000

#define VERSION "0.0.1"
#define VENDOR_NAME "Adafruit Industries"
#define PRODUCT_NAME "Arduino MSC"
#define VOLUME_LABEL "ARDUINO"
#define INDEX_URL "https://adafru.it/featherm0"
#define BOARD_ID "SAMD21G18A-Arduino-v0"

#endif // !_CONFIG_H