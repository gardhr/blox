#include "blox.h"
#include <stdio.h>

int main(int argc, char** argv)
{
 blox text = blox_create(char);
 if(argc == 1)
  blox_append_string(char, text, "Looking backward...");
 for(;;)
 {
  char* data = *(++argv);
  if(data == NULL)
   break;
  blox_append_string(char, text, data);
  blox_append_string(char, text, "\n");
 } 
 while(!blox_empty(text))
 {
  putchar(blox_back(char, text));
  blox_pop(char, text);
 }
 puts("");
 blox_free(text);
}

