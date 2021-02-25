/*
MIT License

Copyright (c) 2021 Sebastian Garth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BLOX_H_INCLUDED
#define BLOX_H_INCLUDED

#include <stdlib.h>
#include <memory.h>

typedef struct
{
 void* data;
 size_t length;
 size_t capacity;
}
 blox;

blox blox_nil(void)
{
 blox nil = {0};
 return nil;
}

#define blox_data(TYPE, buffer) ((TYPE*)(buffer).data)

#define blox_index(TYPE, buffer, index) (blox_data(TYPE, buffer) + (index))

#define blox_get(TYPE, buffer, index) (*blox_index(TYPE, buffer, index))

#define blox_set(TYPE, buffer, index, value)\
(blox_get(TYPE, buffer, index) = (TYPE)(value))

#define blox_length(buffer) (buffer).length

#define blox_empty(buffer) (blox_length(buffer) == 0)

#define blox_capacity(buffer) (buffer).capacity

blox blox_make_(size_t length, size_t size)
{
 blox buffer = {0};
 buffer.data = calloc(length + 1, size);
 buffer.length = buffer.capacity = length;
 return buffer;
}

#define blox_make(TYPE, length) blox_make_(length, sizeof(TYPE))

#define blox_shrink(buffer) ((buffer).length = 0)

#define blox_drop(buffer)\
 do\
 {\
  (buffer).data = NULL;\
  (buffer).length = (buffer).capacity = 0;\
 }\
 while(0)

#define blox_clear_range(TYPE, buffer, start, end)\
 do\
 {\
  size_t begin = (start);\
  size_t length = (end) - begin;\
  memset(blox_index(TYPE, (buffer), begin), 0, length * sizeof(TYPE));\
 }\
 while(0)

#define blox_clear(TYPE, buffer)\
 do\
 {\
  blox_clear_range(TYPE, buffer, 0, (buffer).length);\
 }\
 while(0)

#define blox_insert(TYPE, buffer, index, value)\
 do\
 {\
  size_t position = (index);\
  size_t end = (buffer).length;\
  if(position >= end)\
   blox_resize(TYPE, buffer, position + 1);\
  blox_set(TYPE, buffer, position, (value));\
 }\
 while(0)

#define blox_resize(TYPE, buffer, size)\
 do\
 {\
  size_t request = (size);\
  size_t capacity = (buffer).capacity;\
  if(request > capacity)\
  {\
   size_t expanded = capacity ? capacity : 1;\
   while(expanded < request)\
    expanded <<= 1;\
   (buffer).data = realloc((buffer).data, (expanded + 1) * sizeof(TYPE));\
   (buffer).capacity = expanded;\
  }\
  size_t length = (buffer).length;\
  if(request > length)\
   memset(blox_index(TYPE, buffer, length), 0, ((request - length) + 1) * sizeof(TYPE));\
  (buffer).length = request;\
 }\
 while(0)

#define blox__safe_previous(buffer)\
((buffer).length ? ((buffer).length - 1) : (buffer).length)

#define blox_stuff(TYPE, buffer) blox_resize(TYPE, buffer, blox_length(buffer) + 1)

#define blox_push(TYPE, buffer, value) blox_insert(TYPE, buffer, (buffer).length, value)

#define blox_pop(TYPE, buffer) blox_resize(TYPE, buffer, blox__safe_previous(buffer))

#define blox_front(TYPE, buffer) blox_get(TYPE, buffer, 0)

#define blox_back(TYPE, buffer) blox_get(TYPE, buffer, blox__safe_previous(buffer))

#define blox_begin(TYPE, buffer) blox_index(TYPE, buffer, 0)

#define blox_end(TYPE, buffer) blox_index(TYPE, buffer, (buffer).length)

#define blox_top(TYPE, buffer) blox_index(TYPE, buffer, blox__safe_previous(buffer))

#define blox_append(TYPE, buffer, other)\
 do\
 {\
  size_t length = (buffer).length;\
  size_t additional = (other).length;\
  blox_resize(TYPE, (buffer), length + additional);\
  memcpy(blox_index(TYPE, (buffer), length), (other).data, additional * sizeof(TYPE));\
 }\
 while(0)

#define blox_append_sequence(TYPE, buffer, start, end)\
 do\
 {\
  size_t length = end - start;\
  size_t index = 0;\
  while(index != length)\
   blox_push(TYPE, (buffer), (TYPE)start[index++]);\
 }\
 while(0)

#define blox_append_string(TYPE, buffer, array)\
 do\
 {\
  size_t index = 0;\
  while(array[index])\
   blox_push(TYPE, (buffer), (TYPE)array[index++]);\
 }\
 while(0)

#define blox_append_array(TYPE, buffer, array, length)\
 do\
 {\
  size_t index = 0;\
  while(index < length)\
   blox_push(TYPE, (buffer), (TYPE)array[index++]);\
 }\
 while(0)

blox blox_clone_(blox other, size_t size)
{
 blox buffer = {0};
 size_t length = other.length;
 size_t actual = length * size;
 buffer.data = malloc(actual);
 memcpy(buffer.data, other.data, actual);
 buffer.length = buffer.capacity = length;
 return buffer;
}

#define blox_copy(TYPE, buffer, source)\
 do\
 {\
  blox_shrink(buffer);\
  blox_append(TYPE, (buffer), (source));\
 }\
 while(0)

#define blox_clone(TYPE, buffer) blox_clone_((buffer), sizeof(TYPE))

#define blox_swap(buffer, other)\
 do\
 {\
  blox stored = (buffer);\
  (buffer) = (other);\
  (other) = stored;\
 }\
 while(0)

#define blox_free(buffer)\
 do\
 {\
  free((buffer).data);\
  blox_drop(buffer);\
 }\
 while(0)

#define blox_for_each(TYPE, buffer, action)\
 do\
 {\
  typedef void (*callback)(const void*, size_t);\
  callback step = (callback)action;\
  for(size_t index = 0, length = (buffer).length; index < length; ++index)\
   step(blox_index(TYPE, buffer, index), index);\
 }\
 while(0)

typedef int (*blox_compare)(const void*, const void*);

#define blox_sort(TYPE, buffer, compare)\
 qsort((buffer).data, (buffer).length, sizeof(TYPE), (blox_compare)compare)

#define blox_search(TYPE, buffer, key, compare)\
 ((TYPE*)bsearch(&key, (buffer).data, (buffer).length, sizeof(TYPE), (blox_compare)compare))

#define RETURN_BLOX_COMPARE_ASCENDING(TYPE, left, right)\
TYPE lhs = *left, rhs = *right; return (lhs < rhs ? -1 : lhs > rhs ? 1 : 0)

int blox_char_ascending(char* left, char* right) { RETURN_BLOX_COMPARE_ASCENDING(char, left, right); }
int blox_byte_ascending(unsigned char* left, unsigned char* right) { RETURN_BLOX_COMPARE_ASCENDING(unsigned char, left, right); }
int blox_short_ascending(short* left, short* right) { RETURN_BLOX_COMPARE_ASCENDING(short, left, right); }
int blox_ushort_ascending(unsigned short* left, unsigned short* right) { RETURN_BLOX_COMPARE_ASCENDING(unsigned short, left, right); }
int blox_int_ascending(int* left, int* right) { RETURN_BLOX_COMPARE_ASCENDING(int, left, right); }
int blox_uint_ascending(unsigned int* left, unsigned int* right) { RETURN_BLOX_COMPARE_ASCENDING(unsigned int, left, right); }
int blox_long_ascending(long* left, long* right) { RETURN_BLOX_COMPARE_ASCENDING(long, left, right); }
int blox_ulong_ascending(unsigned long* left, unsigned long* right) { RETURN_BLOX_COMPARE_ASCENDING(unsigned long, left, right); }
int blox_llong_ascending(long long* left, long long* right) { RETURN_BLOX_COMPARE_ASCENDING(long long, left, right); }
int blox_ullong_ascending(unsigned long long* left, unsigned long long* right) { RETURN_BLOX_COMPARE_ASCENDING(unsigned long long, left, right); }
int blox_size_t_ascending(size_t* left, size_t* right) { RETURN_BLOX_COMPARE_ASCENDING(size_t, left, right); }
int blox_float_ascending(float* left, int* right) { RETURN_BLOX_COMPARE_ASCENDING(float, left, right); }
int blox_double_ascending(double* left, double* right) { RETURN_BLOX_COMPARE_ASCENDING(double, left, right); }
int blox_text_ascending(char** left, char** right)
{
 char* lhs = *left;
 char* rhs = *right;
 if(lhs == NULL)
  return -1;
 if(rhs == NULL)
   return 1;
 return strcmp(lhs, rhs);
}

#define RETURN_BLOX_COMPARE_DESCENDING(TYPE, left, right)\
RETURN_BLOX_COMPARE_ASCENDING(TYPE, right, left)

int blox_char_descending(char* left, char* right) { RETURN_BLOX_COMPARE_DESCENDING(char, right, left); }
int blox_byte_descending(unsigned char* left, unsigned char* right) { RETURN_BLOX_COMPARE_DESCENDING(unsigned char, right, left); }
int blox_short_descending(short* left, short* right) { RETURN_BLOX_COMPARE_DESCENDING(short, right, left); }
int blox_ushort_descending(unsigned short* left, unsigned short* right) { RETURN_BLOX_COMPARE_DESCENDING(unsigned short, right, left); }
int blox_int_descending(int* left, int* right) { RETURN_BLOX_COMPARE_DESCENDING(int, right, left); }
int blox_uint_descending(unsigned int* left, unsigned int* right) { RETURN_BLOX_COMPARE_DESCENDING(unsigned int, right, left); }
int blox_long_descending(long* left, long* right) { RETURN_BLOX_COMPARE_DESCENDING(long, right, left); }
int blox_ulong_descending(unsigned long* left, unsigned long* right) { RETURN_BLOX_COMPARE_DESCENDING(unsigned long, right, left); }
int blox_llong_descending(long long* left, long long* right) { RETURN_BLOX_COMPARE_DESCENDING(long long, right, left); }
int blox_ullong_descending(unsigned long long* left, unsigned long long* right) { RETURN_BLOX_COMPARE_DESCENDING(unsigned long long, right, left); }
int blox_size_t_descending(size_t* left, size_t* right) { RETURN_BLOX_COMPARE_DESCENDING(size_t, left, right); }
int blox_float_descending(float* left, int* right) { RETURN_BLOX_COMPARE_DESCENDING(float, right, left); }
int blox_double_descending(double* left, double* right) { RETURN_BLOX_COMPARE_DESCENDING(double, right, left); }
int blox_text_descending(char** left, char** right)
{
 char* lhs = *left;
 char* rhs = *right;
 if(lhs == NULL)
  return 1;
 if(rhs == NULL)
   return -1;
 return strcmp(rhs, lhs);
}

#endif // BLOX_H_INCLUDED

