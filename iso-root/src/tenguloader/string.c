#include "string.h"

size_t strlen(const char* string) {
  size_t n = 0;
  for (n = 0; string[n] != '\0'; n++) ;
  return n;
}
