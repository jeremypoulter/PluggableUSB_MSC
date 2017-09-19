#include "DynamicMtd.h"
#include "fat.h"

DynamicMtd::DynamicMtd() :
  startReadBlock(0),
  numReadBlocks(0)
{
}

uint32_t DynamicMtd::getCapacity() 
{
  return 0;
}

uint32_t DynamicMtd::getBlockSize() 
{
  return 512;
}

MtdRet DynamicMtd::initReadBlocks(uint32_t start, uint16_t nb_block) 
{
  startReadBlock = start;
  numReadBlocks = nb_block;

  return MtdRet_Ok;
}

MtdRet DynamicMtd::startReadBlocks(void *dest, uint16_t nb_block) 
{
  uint8_t *ptr = (uint8_t *)dest;
  for(uint16_t i = 0; i < nb_block; i++)
  {
    fat_read_block(startReadBlock + i, ptr);
    ptr += getBlockSize();
  }

  return MtdRet_Ok;
}

MtdRet DynamicMtd::waitEndOfReadBlocks(bool abort) 
{
  return MtdRet_Ok;
}
