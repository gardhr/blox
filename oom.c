#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "blox.h"

int main(void)
{
 blox data = {0};
 size_t insane = 1000000000000;
 blox_resize(int, data, insane);
 if(data.length != insane)
  puts("Failed to allocate insane amount of memory");
 else
  puts("Impressive!");
 return 0;
}

