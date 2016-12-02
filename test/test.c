#include "../src/synthdef.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("usage: %s <input_synthdef> <output_synthdef>\n", argv[0]);
    return 1;
  }

  FILE *fileIn;
  if ((fileIn = fopen(argv[1], "rb")) == NULL) {
    printf("File does not exist: %s\n", argv[1]);
    fclose(fileIn);
    return 1;
  }
  sc_t sc;
  int readSuccess = readSynthDef(fileIn, &sc);
  fclose(fileIn);

  if (readSuccess) {
    FILE *fileOut = fopen(argv[2], "wb");
    int writeSuccess = writeSynthDef(fileOut, sc);
    freeSynthDef(sc);
    fclose(fileOut);
    if (!writeSuccess) {
      printf("Error writing file.\n");
      return 1;
    }
  } else {
    if (sc != NULL)
      freeSynthDef(sc);
    printf("Error reading file.\n");
    return 1;
  }

  return 0;
}
