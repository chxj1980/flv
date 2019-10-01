#ifndef FLV_UTILS_HEADER
#define FLV_UTILS_HEADER

#include <stdio.h>
#include "types.h"

long read_big(byte *bytes, int size)
{
  long result = 0;
  for (int i = 0; i < size; ++i)
  {
    result = (result << 8) | bytes[i];
  }
  return result;
}

#endif // !FLV_UTILS_HEADER