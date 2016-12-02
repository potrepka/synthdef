#include "byteio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_LITTLE_ENDIAN (*(uint16_t *)"\0\xff" > 0x100)
#define BYTE_IO_DEBUG 1

short swapShort(short v) { return (v << 8) | ((v >> 8) & 0xFF); }

int swapInt(int v) {
  v = ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0xFF00FF);
  return (v << 16) | ((v >> 16) & 0xFFFF);
}

int readChar(FILE *fp, char *vp) {
  return fread((void *)vp, sizeof(*vp), 1, fp);
}

int writeChar(FILE *fp, char v) {
  return fwrite((void *)(&v), sizeof(v), 1, fp);
}

int readShort(FILE *fp, short *vp) {
  int success = fread((void *)vp, sizeof(*vp), 1, fp);
  if (success && IS_LITTLE_ENDIAN)
    *vp = swapShort(*vp);
  return success;
}

int writeShort(FILE *fp, short v) {
  if (IS_LITTLE_ENDIAN)
    v = swapShort(v);
  return fwrite((void *)(&v), sizeof(v), 1, fp);
}

int readInt(FILE *fp, int *vp) {
  int success = fread((void *)vp, sizeof(*vp), 1, fp);
  if (success && IS_LITTLE_ENDIAN)
    *vp = swapInt(*vp);
  return success;
}

int writeInt(FILE *fp, int v) {
  if (IS_LITTLE_ENDIAN)
    v = swapInt(v);
  return fwrite((void *)(&v), sizeof(v), 1, fp);
}

int readFloat(FILE *fp, float *vp) {
  return fread((void *)vp, sizeof(*vp), 1, fp);
}

int writeFloat(FILE *fp, float v) {
  return fwrite((void *)(&v), sizeof(v), 1, fp);
}
