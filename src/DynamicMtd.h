#ifndef _DYNAMIC_MTD_H
#define _DYNAMIC_MTD_H

#include "mtd.h"

class DynamicMtd : public Mtd
{
private:
  uint32_t startReadBlock;
  uint16_t numReadBlocks;

public:
  DynamicMtd();

  MtdState getState() {
    return MtdState_Ready;
  }
  uint32_t getCapacity();
  uint32_t getBlockSize();
  MtdRet initReadBlocks(uint32_t start, uint16_t nb_block);
  MtdRet startReadBlocks(void *dest, uint16_t nb_block);
  MtdRet waitEndOfReadBlocks(bool abort);

};

#endif // !_DYNAMIC_MTD_H