#include "string_copy.h"

#include <stdlib.h>
#include <string.h>

char* string_copy(const char* s)
{
  char* result;
  int l;

  if (s == 0)
    return 0;

  l = strlen(s) + 1;

  result = (char*) malloc(sizeof(char) * l);
  memcpy(result, s, l);

  return result;
}
