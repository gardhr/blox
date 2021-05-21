#include <stdio.h>
#include "blox.h"

void print_int(int* ptr) {
  printf("%d, ", *ptr);
}

int compare_int(int* lhs, int* rhs) {
  return *lhs - *rhs;
}

void show(const char* preamble, blox box) {
  printf("\n- %s -\n", preamble);
  blox_for_each(int, box, print_int);
  puts("");
}

int main(int argc, char** argv) {
  // Notice that `arr` is "zero terminated"
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 0};

  // Make a copy, treating `arr` as a "string" of ints
  blox cpy = blox_from_string(int, arr);

  // Use `arr` as if it were a blox object
  blox use = blox_use_string(int, arr);

  show("Array", use);

  blox_unshift_by(int, cpy, 4);
  show("After blox_unshift_by 4", cpy);

  blox_prepend(int, cpy, use);
  show("After prepend with original", cpy);

  blox_erase_at(int, cpy, 5, 3);
  show("After erasing 3 elements, starting from the 5th index", cpy);

  blox_erase(int, cpy, 2);
  show("After erasing 2nd element", cpy);

  blox_splice_string(int, cpy, 4, arr);
  show("After splicing array into copy at the 4th element", cpy);

  blox slc = blox_slice_first(int, cpy, 6);
  show("Slice of first 6 elements", slc);

  blox_sort(int, slc, compare_int);
  show("Sorted", slc);

  blox_shift_by(int, slc, 2);
  show("blox_shift_by 2", slc);

  blox_pop(int, slc);
  show("blox_pop", slc);

  blox_shift(int, slc);
  show("blox_shift", slc);

  blox_append(int, slc, use);
  show("blox_append original array", slc);

  blox_free(slc);

  if (!blox_empty(slc))
    puts("Impossible, object was freed!");

  blox_free(cpy);

  return 0;
}

