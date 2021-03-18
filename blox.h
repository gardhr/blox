/* Blox Array Library

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

#define blox_data(TYPE, buffer) ((TYPE*)(buffer).data)

#define blox_index(TYPE, buffer, index) (blox_data(TYPE, buffer) + (index))

#define blox_get(TYPE, buffer, index) (*blox_index(TYPE, buffer, index))

#define blox_set(TYPE, buffer, index, value)\
(blox_get(TYPE, buffer, index) = (TYPE)(value))

#define blox_length(buffer) (buffer).length

#define blox_empty(buffer) (blox_length(buffer) == 0)

#define blox_capacity(buffer) (buffer).capacity

blox blox_make_(size_t width, size_t length, int empty)
{
 blox buffer = {0};
 buffer.data = calloc(length + 1, width);
 buffer.capacity = length;
 if(!empty)
  buffer.length = length;
 return buffer;
}

#define blox_make(TYPE, length)\
 blox_make_(sizeof(TYPE), length, 0)

#define blox_from_string(TYPE, string)\
 blox_clone(TYPE, blox_use_string(TYPE, string))

blox blox_use_(const void* address, size_t length)
{
 blox buffer = {(void*)address, length, length};
 return buffer;
}

#define blox_use(array, length)\
 blox_use_(array, length)

#include "tools.h"

blox blox_use_string_(size_t width, const void* address)
{
 typedef unsigned char byte;
 byte* base = ((byte*)address);
 byte* current = base;
 for(;;)
 {
  size_t count = width;
  do
  {
   if(*current != 0)
   {
    current += count;
    break;
   }
   else
    ++current;
  }
  while(--count);
  if(count == 0)
   break;
 }
 size_t length = (current - base) - 1;
 blox buffer = {base, length, length};
 return buffer;
}

#define blox_use_string(TYPE, string)\
 blox_use_string_(sizeof(TYPE), string)

#define blox_reserved(TYPE, length)\
 blox_make_(sizeof(TYPE), length, 1)

#define blox_create(TYPE) blox_make(TYPE, 0)

#define blox_shrink(TYPE, buffer) blox_resize(TYPE, buffer, 0)

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
  if(request >= capacity)\
  {\
   if(capacity == 0)\
    ++capacity;\
   while(capacity <= request)\
    capacity <<= 1;\
   (buffer).data = realloc((buffer).data, capacity * sizeof(TYPE));\
   (buffer).capacity = capacity;\
  }\
  size_t length = (buffer).length;\
  if(request > length)\
   memset(blox_index(TYPE, buffer, length), 0, ((request - length) + 1) * sizeof(TYPE));\
  else\
   memset(blox_index(TYPE, buffer, request), 0, sizeof(TYPE));\
  (buffer).length = request;\
 }\
 while(0)

#define blox_reserve(TYPE, buffer, size)\
 do\
 {\
  size_t saved = (buffer).length;\
  blox_resize(TYPE, buffer, size);\
  (buffer).length = saved;\
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

blox blox_clone_(blox other, size_t width)
{
 size_t length = other.length;
 size_t size = length * width;
 blox buffer = blox_make(char, size);
 memcpy(buffer.data, other.data, size);
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

#define blox_reverse(TYPE, buffer)\
 do\
 {\
  TYPE* left = blox_begin(TYPE, buffer);\
  TYPE* right = blox_end(TYPE, buffer);\
  TYPE swap;\
  while(left < --right)\
  {\
   swap = *left;\
   *left++ = *right;\
   *right = swap;\
  }\
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

#define blox_visit(TYPE, buffer, action, userdata)\
 do\
 {\
  typedef void (*callback)(const void*, void*);\
  callback step = (callback)action;\
  for(size_t index = 0, length = (buffer).length; index < length; ++index)\
   step(blox_index(TYPE, buffer, index), userdata);\
 }\
 while(0)

typedef int (*blox_comparison)(const void*, const void*);

#define blox_sort(TYPE, buffer, comparison)\
 qsort((buffer).data, (buffer).length, sizeof(TYPE), (blox_comparison)comparison)

#define blox_search(TYPE, buffer, key, comparison)\
 ((TYPE*)bsearch(&key, (buffer).data, (buffer).length, sizeof(TYPE), (blox_comparison)comparison))

int blox_compare_(void* lhs, size_t lmx, void* rhs, size_t rmx, size_t width)
{
 if(lmx != rmx)
  return lmx < rmx ? -1 : 1;
 return memcmp(lhs, rhs, lmx * width);
}

#define blox_compare(TYPE, lbx, rbx)\
 blox_compare_((lbx).data, (lbx).length, (rbx).data, (rbx).length, sizeof(TYPE))

#define blox_equal(TYPE, lbx, rbx)\
 (blox_compare(TYPE, lbx, rbx) == 0)

#define blox_less(TYPE, lbx, rbx)\
 (blox_compare(TYPE, lbx, rbx) < 0)

#define blox_less_or_equal(TYPE, lbx, rbx)\
 (blox_compare(TYPE, lbx, rbx) <= 0)

#define blox_greater(TYPE, lbx, rbx)\
 (blox_compare(TYPE, lbx, rbx) > 0)

#define blox_greater_or_equal(TYPE, lbx, rbx)\
 (blox_compare(TYPE, lbx, rbx) >= 0)

#endif // BLOX_H_INCLUDED

