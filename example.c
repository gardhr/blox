#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blox.h"

typedef struct {
  blox tag;
  /*
   ...
  */
} info;

info make_info(const char* tag) {
  info fyi = {0};
  blox_append_string(char, fyi.tag, tag);
  return fyi;
}

void free_info(info* my) {
  blox_free(my->tag);
}

void print_info(info* my) {
  printf("TAG: %s\n", blox_begin(char, my->tag));
}

int compare_info(info* lhs, info* rhs) {
  return strcmp(blox_data(char, lhs->tag), blox_data(char, rhs->tag));
}

void reverse_info(info* my) {
  blox_reverse(char, my->tag);
}

void print_int(int* ptr) {
  printf("%d, ", *ptr);
}

int compare_int(int* lhs, int* rhs) {
  return *lhs - *rhs;
}

int main(int argc, char** argv) {
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

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0};
  blox cpy = blox_from_string(int, arr);
  
  puts("\nBefore blox_unshift_by:");
  blox_for_each(int, cpy, print_int);
  puts("");

  blox_unshift_by(int, cpy, 4);

  puts("\nAfter blox_unshift_by(int, cpy, 4):");

  blox_for_each(int, cpy, print_int);
  puts("");

  blox_append_string(int, cpy, arr);
  puts("\nAfter append:");

  blox_for_each(int, cpy, print_int);
  puts("");

  blox_erase_range(int, cpy, 5, 7);
  puts("\nAfter erase from the 5th index up to (but excluding) 7th:");

  blox_for_each(int, cpy, print_int);
  puts("");
  
  blox_free(cpy);
  return 0;
}

