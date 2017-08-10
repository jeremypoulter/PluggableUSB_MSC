#ifndef __MTD_H
#define __MTD_H

#include <Arduino.h>

typedef enum {
  MtdRet_Ok,
  MtdRet_Empty, /* No media */
  MtdRet_NotImplemented /* API not implemented */
} MtdRet;

typedef enum {
  MtdState_Ready,
  MtdState_Empty /* No media */
} MtdState;

class Mtd
{
  public:
    Mtd() {
    }
    MtdState getState() {
      return MtdState_Empty;
    }
    uint32_t getCapacity() {
      return 0;
    }
    uint32_t getBlockSize() {
      return 512;
    }

    /**
     * \brief Initialize the read blocks of data from the device.
     *
     * \param start    Start block number to to read.
     * \param nb_block Total number of blocks to be read.
     *
     * \return return MtdRet_Ok if success,
     *         otherwise return an error code (\ref MtdRet).
     */
    MtdRet initReadBlocks(uint32_t start, uint16_t nb_block) {
      return MtdRet_NotImplemented;
    }

    /**
     * \brief Start the read blocks of data from the device.
     *
     * \param dest     Pointer to read buffer.
     * \param nb_block Number of blocks to be read.
     *
     * \return return MtdRet_Ok if started,
     *         otherwise return an error code (\ref MtdRet).
     */
    MtdRet startReadBlocks(void *dest, uint16_t nb_block) {
      return MtdRet_NotImplemented;
    }

    /**
     * \brief Wait the end of read blocks of data from the device.
     *
     * \param abort Abort reading process initialized by
     *              \ref initReadBlocks() after the reading issued by
     *              \ref startReadBlocks() is done
     *
     * \return return MtdRet_Ok if success,
     *         otherwise return an error code (\ref MtdRet).
     */
    MtdRet waitEndOfReadBlocks(bool abort) {
      return MtdRet_NotImplemented;
    }

    /**
     * \brief Initialize the write blocks of data
     *
     * \param start    Start block number to be written.
     * \param nb_block Total number of blocks to be written.
     *
     * \return return MtdRet_Ok if success,
     *         otherwise return an error code (\ref MtdRet).
     */
    MtdRet initWriteBlocks(uint32_t start, uint16_t nb_block) {
      return MtdRet_NotImplemented;
    }

    /**
    * \brief Start the write blocks of data
    *
    * \param src      Pointer to write buffer.
    * \param nb_block Number of blocks to be written.
    *
    * \return return MtdRet_Ok if started,
    *         otherwise return an error code (\ref MtdRet).
    */
    MtdRet startWriteBlocks(const void *src, uint16_t nb_block) {
      return MtdRet_NotImplemented;
    }

    /**
    * \brief Wait the end of write blocks of data
    *
    * \param abort Abort writing process initialized by
    *              \ref initWriteBlocks() after the writing issued by
    *              \ref startWriteBlocks() is done
    *
    * \return return MtdRet_Ok if success,
    *         otherwise return an error code (\ref MtdRet).
    */
    MtdRet waitEndOfWriteBlocks(bool abort) {
      return MtdRet_NotImplemented;
    }
};

#endif 