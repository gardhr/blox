#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "blox.h"

typedef struct
{
 blox tag;
/*
 ...
*/
}
 info;

info make_info(const char* tag)
{
 info fyi = {0};
 blox_append_string(char, fyi.tag, tag);
 return fyi;
}

int compare_info(info* lhs, info* rhs)
{
 puts(blox_data(char, lhs->tag));
 return strcmp(blox_data(char, lhs->tag), blox_data(char, rhs->tag));
}

void print_info(info* my)
{
 printf("TAG: %s\n", blox_begin(char, my->tag));
}

void free_info(info* my)
{
 blox_free(my->tag);
}

void reverse_info(info* my)
{
 blox_reverse(char, my->tag);
}

int main(int argc, char** argv)
{
 blox stuff = {0};

 blox_push(info, stuff, make_info("Third"));
 blox_push(info, stuff, make_info("Fourth"));
 blox_unshift(info, stuff, make_info("Second"));
 blox_unshift(info, stuff, make_info("First"));

 puts("\nInfo:");
 blox_for_each(info, stuff, print_info);

 blox_sort(info, stuff, compare_info);
 puts("\nSorted:");
 blox_for_each(info, stuff, print_info);

 blox_for_each(info, stuff, reverse_info);
 puts("\ndesreveR:");
 blox_for_each(info, stuff, print_info);

 blox_for_each(info, stuff, free_info);
 blox_free(stuff);
 return 0;
}

