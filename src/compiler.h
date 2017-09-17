// ASF -> Arduino type/support compatibility

#ifndef UTILS_COMPILER_H_INCLUDED
#define UTILS_COMPILER_H_INCLUDED

#include <Arduino.h>

#define COMPILER_PRAGMA(arg)            _Pragma(#arg)
#define COMPILER_PACK_SET(alignment)    COMPILER_PRAGMA(pack(alignment))
#define COMPILER_PACK_RESET()           COMPILER_PRAGMA(pack())
#define COMPILER_ALIGNED(a) __attribute__((__aligned__(a)))
#define COMPILER_WORD_ALIGNED __attribute__((__aligned__(4)))

typedef uint16_t                le16_t;
typedef uint16_t                be16_t;
typedef uint32_t                le32_t;
typedef uint32_t                be32_t;

#define swap16(u16) ((uint16_t)(((uint16_t)(u16) >> 8) | \
                                ((uint16_t)(u16) << 8)))

#define BE16(x) swap16(x)
#define LE16(x) (x)

#define le16_to_cpu(x) (x)
#define cpu_to_le16(x) (x)
#define LE16_TO_CPU(x) (x)
#define CPU_TO_LE16(x) (x)

#define be16_to_cpu(x) swap16(x)
#define cpu_to_be16(x) swap16(x)
#define BE16_TO_CPU(x) swap16(x)
#define CPU_TO_BE16(x) swap16(x)

#define le32_to_cpu(x) (x)
#define cpu_to_le32(x) (x)
#define LE32_TO_CPU(x) (x)
#define CPU_TO_LE32(x) (x)

#define be32_to_cpu(x) swap32(x)
#define cpu_to_be32(x) swap32(x)
#define BE32_TO_CPU(x) swap32(x)
#define CPU_TO_BE32(x) swap32(x)

#define swap32(u32) ((uint32_t)__builtin_bswap32((uint32_t)(u32)))

#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)

#define  be32_to_cpu(x) swap32(x)
#define  cpu_to_be32(x) swap32(x)
#define  BE32_TO_CPU(x) swap32(x)
#define  CPU_TO_BE32(x) swap32(x)

typedef int8_t                  S8 ;  //!< 8-bit signed integer.
typedef uint8_t                 U8 ;  //!< 8-bit unsigned integer.
typedef int16_t                 S16;  //!< 16-bit signed integer.
typedef uint16_t                U16;  //!< 16-bit unsigned integer.
typedef int32_t                 S32;  //!< 32-bit signed integer.
typedef uint32_t                U32;  //!< 32-bit unsigned integer.
typedef int64_t                 S64;  //!< 64-bit signeds integer.
typedef uint64_t                U64;  //!< 64-bit unsigned integer.
typedef float                   F32;  //!< 32-bit floating-point number.
typedef double                  F64;  //!< 64-bit floating-point number.

#define MSB(u16) (((U8 *)&(u16))[1]) //!< Most significant byte of \a u16.
#define LSB(u16) (((U8 *)&(u16))[0]) //!< Least significant byte of \a u16.

#define MSH(u32) (((U16 *)&(u32))[1])  //!< Most significant half-word of \a u32.
#define LSH(u32) (((U16 *)&(u32))[0])  //!< Least significant half-word of \a u32.
#define MSB0W(u32) (((U8 *)&(u32))[3]) //!< Most significant byte of 1st rank of \a u32.
#define MSB1W(u32) (((U8 *)&(u32))[2]) //!< Most significant byte of 2nd rank of \a u32.
#define MSB2W(u32) (((U8 *)&(u32))[1]) //!< Most significant byte of 3rd rank of \a u32.
#define MSB3W(u32) (((U8 *)&(u32))[0]) //!< Most significant byte of 4th rank of \a u32.
#define LSB3W(u32) MSB0W(u32)          //!< Least significant byte of 4th rank of \a u32.
#define LSB2W(u32) MSB1W(u32)          //!< Least significant byte of 3rd rank of \a u32.
#define LSB1W(u32) MSB2W(u32)          //!< Least significant byte of 2nd rank of \a u32.
#define LSB0W(u32) MSB3W(u32)          //!< Least significant byte of 1st rank of \a u32.

#define MSW(u64) (((U32 *)&(u64))[1])  //!< Most significant word of \a u64.
#define LSW(u64) (((U32 *)&(u64))[0])  //!< Least significant word of \a u64.
#define MSH0(u64) (((U16 *)&(u64))[3]) //!< Most significant half-word of 1st rank of \a u64.
#define MSH1(u64) (((U16 *)&(u64))[2]) //!< Most significant half-word of 2nd rank of \a u64.
#define MSH2(u64) (((U16 *)&(u64))[1]) //!< Most significant half-word of 3rd rank of \a u64.
#define MSH3(u64) (((U16 *)&(u64))[0]) //!< Most significant half-word of 4th rank of \a u64.
#define LSH3(u64) MSH0(u64)            //!< Least significant half-word of 4th rank of \a u64.
#define LSH2(u64) MSH1(u64)            //!< Least significant half-word of 3rd rank of \a u64.
#define LSH1(u64) MSH2(u64)            //!< Least significant half-word of 2nd rank of \a u64.
#define LSH0(u64) MSH3(u64)            //!< Least significant half-word of 1st rank of \a u64.
#define MSB0D(u64) (((U8 *)&(u64))[7]) //!< Most significant byte of 1st rank of \a u64.
#define MSB1D(u64) (((U8 *)&(u64))[6]) //!< Most significant byte of 2nd rank of \a u64.
#define MSB2D(u64) (((U8 *)&(u64))[5]) //!< Most significant byte of 3rd rank of \a u64.
#define MSB3D(u64) (((U8 *)&(u64))[4]) //!< Most significant byte of 4th rank of \a u64.
#define MSB4D(u64) (((U8 *)&(u64))[3]) //!< Most significant byte of 5th rank of \a u64.
#define MSB5D(u64) (((U8 *)&(u64))[2]) //!< Most significant byte of 6th rank of \a u64.
#define MSB6D(u64) (((U8 *)&(u64))[1]) //!< Most significant byte of 7th rank of \a u64.
#define MSB7D(u64) (((U8 *)&(u64))[0]) //!< Most significant byte of 8th rank of \a u64.
#define LSB7D(u64) MSB0D(u64)          //!< Least significant byte of 8th rank of \a u64.
#define LSB6D(u64) MSB1D(u64)          //!< Least significant byte of 7th rank of \a u64.
#define LSB5D(u64) MSB2D(u64)          //!< Least significant byte of 6th rank of \a u64.
#define LSB4D(u64) MSB3D(u64)          //!< Least significant byte of 5th rank of \a u64.
#define LSB3D(u64) MSB4D(u64)          //!< Least significant byte of 4th rank of \a u64.
#define LSB2D(u64) MSB5D(u64)          //!< Least significant byte of 3rd rank of \a u64.
#define LSB1D(u64) MSB6D(u64)          //!< Least significant byte of 2nd rank of \a u64.
#define LSB0D(u64) MSB7D(u64)          //!< Least significant byte of 1st rank of \a u64.

#define LSB0(u32) LSB0W(u32) //!< Least significant byte of 1st rank of \a u32.
#define LSB1(u32) LSB1W(u32) //!< Least significant byte of 2nd rank of \a u32.
#define LSB2(u32) LSB2W(u32) //!< Least significant byte of 3rd rank of \a u32.
#define LSB3(u32) LSB3W(u32) //!< Least significant byte of 4th rank of \a u32.
#define MSB3(u32) MSB3W(u32) //!< Most significant byte of 4th rank of \a u32.
#define MSB2(u32) MSB2W(u32) //!< Most significant byte of 3rd rank of \a u32.
#define MSB1(u32) MSB1W(u32) //!< Most significant byte of 2nd rank of \a u32.
#define MSB0(u32) MSB0W(u32) //!< Most significant byte of 1st rank of \a u32.

#endif /* UTILS_COMPILER_H_INCLUDED */
