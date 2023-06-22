#include "string.h"

void* memcpy(uint8_t* dest, const uint8_t* src, size_t n) {
  for (size_t i = 0; i < n; i++)
    dest[i] = src[i];
  return dest;
}

size_t strlen(const char* string) {
  size_t n = 0;
  for (n = 0; string[n] != '\0'; n++) ;
  return n;
}

void strcpy(char* dest, const char* src) {
  size_t i;
  for (i = 0; i < strlen(src); i++)
    dest[i] = src[i];
  dest[i] = '\0';
}

void strcat(char* dest, const char* src) {
  char* tmp = dest;
  for (size_t i = 0; dest[i] != 0; i++)
    tmp++;
  strcpy(tmp, src);
}
