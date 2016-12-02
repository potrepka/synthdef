#ifndef _byteio_h
#define _byteio_h

short swapShort(short v);
int swapInt(int v);

int readChar(FILE *fp, char *vp);
int writeChar(FILE *fp, char v);

int readShort(FILE *fp, short *vp);
int writeShort(FILE *fp, short v);

int readInt(FILE *fp, int *vp);
int writeInt(FILE *fp, int v);

int readFloat(FILE *fp, float *vp);
int writeFloat(FILE *fp, float v);

#endif
