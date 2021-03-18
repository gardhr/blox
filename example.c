#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "blox.h"

typedef struct
{
 blox tag;
 int id;
}
 info;

info make_info(const char* tag, int id)
{
 info fyi = {0};
 blox_append_string(char, fyi.tag, tag);
 fyi.id = id;
 return fyi;
}

int compare_info(info* lhs, info* rhs)
{
 return strcmp(blox_data(char, lhs->tag), blox_data(char, rhs->tag));
}

void print_info(info* my)
{
 printf("ID: %d\n", my->id);
 printf("TAG: %s\n", blox_begin(char, my->tag));
}

void free_info(info* my)
{
 my->id = 0;
 blox_free(my->tag);
}

void reverse_info(info* my)
{
 my->id = -my->id;
 blox stack = {0};
 blox_swap(stack, my->tag);
 while(!blox_empty(stack))
 {
  blox_push(char, my->tag, blox_back(char, stack));
  blox_pop(char, stack);
 }
 blox_free(stack);
}

int main(int argc, char** argv)
{
 srand(time(NULL));
 blox stuff = {0};
 blox_push(info, stuff, make_info("Something", rand()));
 blox_push(info, stuff, make_info("Another Thing", rand()));
 blox_push(info, stuff, make_info("Nothing", 0));

 blox_sort(info, stuff, compare_info);
 puts("\nInfo:");
 blox_for_each(info, stuff, print_info);

 blox_for_each(info, stuff, reverse_info);
 blox_sort(info, stuff, compare_info);
 puts("\nofnI:");
 blox_for_each(info, stuff, print_info);

 blox_for_each(info, stuff, reverse_info);
 blox_sort(info, stuff, compare_info);
 puts("\nInfo:");
 blox_for_each(info, stuff, print_info);

 blox_for_each(info, stuff, free_info);
 blox_free(stuff);
 return 0;
}

