// ASF -> Arduino type/support compatibility

#ifndef UTILS_COMPILER_H_INCLUDED
#define UTILS_COMPILER_H_INCLUDED

#include <Arduino.h>

#define swap32(u32) ((uint32_t)__builtin_bswap32((uint32_t)(u32)))

#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)

#define  be32_to_cpu(x) swap32(x)
#define  cpu_to_be32(x) swap32(x)
#define  BE32_TO_CPU(x) swap32(x)
#define  CPU_TO_BE32(x) swap32(x)

#endif /* UTILS_COMPILER_H_INCLUDED */
