#include "util.h"
#include <stdio.h>
#include <stdlib.h>

char* read_entire_file(char* filename) {
  FILE* file = fopen(filename, "rb");
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  rewind(file);
  char* ret = malloc(length+1);
  fread(ret, length, 1, file);
  fclose(file);
  ret[length] = '\0';
  return ret;
}
