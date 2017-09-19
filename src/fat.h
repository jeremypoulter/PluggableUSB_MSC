#ifndef _FAT_H
#define _FAT_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void fat_read_block(uint32_t block_no, uint8_t *data);
void fat_write_block(uint32_t block_no, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif // _FAT_H
