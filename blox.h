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

#include <memory.h>
#include <stdlib.h>

typedef struct {
  void* data;
  size_t length;
  size_t capacity;
} blox;

typedef void* (*blox_allocator)(void*, size_t);

blox_allocator blox_realloc(blox_allocator reset) {
  static blox_allocator alloc = realloc;
  if (reset)
    alloc = reset;
  return alloc;
}

blox blox_nil(void) {
  blox nil = {0};
  return nil;
}

#define blox_data(TYPE, buffer) ((TYPE*)(buffer).data)

#define blox_index(TYPE, buffer, index) (blox_data(TYPE, buffer) + (index))

#define blox_get(TYPE, buffer, index) (*blox_index(TYPE, buffer, index))

#define blox_set(TYPE, buffer, index, value) \
  (blox_get(TYPE, buffer, index) = (TYPE)(value))

#define blox_length(buffer) (buffer).length

#define blox_empty(buffer) (blox_length(buffer) == 0)

#define blox_capacity(buffer) (buffer).capacity

#define blox_make(TYPE, length) blox_make_(sizeof(TYPE), length, 0)

blox blox_use_(const void* data, size_t length) {
  blox buffer = {(void*)data, length, length};
  return buffer;
}

#define blox__safe_subtract(a, b) (a < b ? 0 : a - b)

#define blox_use(array, length) blox_use_(array, length)

#define blox_use_array(TYPE, array, length) blox_use(array, length)

#define blox_use_sequence(TYPE, start, end) blox_use(start, end - start)

#define blox_use_view(TYPE, other, start, length) \
  blox_use(blox_index(TYPE, other, start), length)

#define blox_use_window(TYPE, other, start, end) \
  blox_use_view(other, start, blox__safe_subtract(end, start))

#define blox__safe_last(buffer) blox__safe_subtract((buffer).length, 1)

#define blox_use_string(TYPE, string) blox_use_string_(sizeof(TYPE), string)

#define blox_from_array(TYPE, array, length) \
  blox_clone(TYPE, blox_use_array(TYPE, array, length))

#define blox_from_string(TYPE, string) \
  blox_clone(TYPE, blox_use_string(TYPE, string))

#define blox_from_sequence(TYPE, start, end) \
  blox_clone(TYPE, blox_use_sequence(TYPE, start, end))

#define blox_reserved(TYPE, length) blox_make_(sizeof(TYPE), length, 1)

#define blox_create(TYPE) blox_make(TYPE, 0)

#define blox_slice(TYPE, buffer, start, amount) \
  blox_clone(TYPE, blox_use_view(TYPE, buffer, start, amount))

#define blox_slice_range(TYPE, buffer, start, end) \
  blox_slice(TYPE, buffer, start, blox__safe_subtract(end, start))

#define blox_slice_end(TYPE, buffer, start) \
 blox_slice_range(TYPE, buffer, start, (buffer).length))

#define blox_slice_first(TYPE, buffer, amount) \
  blox_slice(TYPE, buffer, 0,                  \
             amount < (buffer).length ? amount : (buffer).length)

#define blox_slice_last(TYPE, buffer, amount)                            \
  blox_slice(TYPE, buffer, blox__safe_subtract((buffer).length, amount), \
             amount < (buffer).length ? amount : 0)

#define blox_shrink(TYPE, buffer) blox_resize(TYPE, buffer, 0)

#define blox_drop(buffer)                    \
  do {                                       \
    (buffer).data = NULL;                    \
    (buffer).length = (buffer).capacity = 0; \
  } while (0)

#define blox_clear_at(TYPE, buffer, start, amount)      \
  do {                                                  \
    TYPE* cursor = blox_index(TYPE, (buffer), (start)); \
    if ((cursor + amount) >= blox_end(TYPE, (buffer)))  \
      break;                                            \
    memset(cursor, 0, amount * sizeof(TYPE));           \
  } while (0)

#define blox_clear_range(TYPE, buffer, start, end) \
  blox_clear_at(TYPE, buffer, start, blox__safe_subtract(end, start))

#define blox_clear_end(TYPE, buffer, start) \
  blox_clear_at(TYPE, buffer, start,        \
                blox__safe_subtract((buffer).length, start))

#define blox_clear(TYPE, buffer) blox_clear_end(TYPE, buffer, 0)

#define blox_erase(TYPE, buffer, index) blox_erase_at(TYPE, buffer, index, 1)

#define blox_erase_at(TYPE, buffer, start, amount)                    \
  do {                                                                \
    TYPE* begin = blox_index(TYPE, (buffer), start);                  \
    size_t length = (buffer).length;                                  \
    memmove(begin, begin + amount, sizeof(TYPE) * (length - amount)); \
    blox_shrink_by(TYPE, (buffer), amount);                           \
  } while (0)

#define blox_erase_range(TYPE, buffer, start, end) \
  blox_erase_at(TYPE, buffer, start, blox__safe_subtract(end, start))

#define blox_insert(TYPE, buffer, index, value) \
  do {                                          \
    size_t position = (index);                  \
    size_t end = (buffer).length;               \
    if (position >= end)                        \
      blox_resize(TYPE, buffer, position + 1);  \
    blox_set(TYPE, buffer, position, (value));  \
  } while (0)

#define blox_resize(TYPE, buffer, size)                               \
  do {                                                                \
    size_t request = (size);                                          \
    size_t capacity = (buffer).capacity;                              \
    size_t length = (buffer).length;                                  \
    if (request == length)                                            \
      break;                                                          \
    if (request >= capacity) {                                        \
      if (!capacity)                                                  \
        ++capacity;                                                   \
      while (capacity <= request)                                     \
        capacity <<= 1;                                               \
      void* chunk =                                                   \
          blox_realloc(NULL)((buffer).data, capacity * sizeof(TYPE)); \
      if (chunk == NULL)                                              \
        break;                                                        \
      (buffer).data = chunk;                                          \
      (buffer).capacity = capacity;                                   \
    }                                                                 \
    if (request > length)                                             \
      memset(blox_index(TYPE, buffer, length), 0,                     \
             ((request - length) + 1) * sizeof(TYPE));                \
    else                                                              \
      memset(blox_index(TYPE, buffer, request), 0, sizeof(TYPE));     \
    (buffer).length = request;                                        \
  } while (0)

#define blox_reserve(TYPE, buffer, size) \
  do {                                   \
    size_t saved = (buffer).length;      \
    blox_resize(TYPE, buffer, size);     \
    (buffer).length = saved;             \
  } while (0)

#define blox_stuff(TYPE, buffer) \
  blox_resize(TYPE, buffer, blox_length(buffer) + 1)

#define blox_push(TYPE, buffer, value) \
  blox_insert(TYPE, buffer, (buffer).length, value)

#define blox_pop(TYPE, buffer) \
  blox_resize(TYPE, buffer, blox__safe_last(buffer))

#define blox_front(TYPE, buffer) blox_get(TYPE, buffer, 0)

#define blox_back(TYPE, buffer) blox_get(TYPE, buffer, blox__safe_last(buffer))

#define blox_begin(TYPE, buffer) blox_index(TYPE, buffer, 0)

#define blox_end(TYPE, buffer) blox_index(TYPE, buffer, (buffer).length)

#define blox_top(TYPE, buffer) blox_index(TYPE, buffer, blox__safe_last(buffer))

#define blox_bottom(TYPE, buffer) \
  blox_index(TYPE, buffer, buffer.length ? -1 : 0)

#define blox_shrink_by(TYPE, buffer, amount) \
  do {                                       \
    size_t length = blox_length(buffer);     \
    if (amount <= length)                    \
      length -= amount;                      \
    blox_resize(TYPE, buffer, length);       \
  } while (0)

#define blox_shift_by(TYPE, buffer, amount)        \
  do {                                             \
    if (amount == 0)                               \
      break;                                       \
    TYPE* begin = blox_begin(TYPE, (buffer));      \
    TYPE* cursor = begin + (amount);           \
    if (cursor > blox_end(TYPE, (buffer)))         \
      break;                                       \
    memmove(begin, cursor, sizeof(TYPE) * ((buffer).length - (amount))); \
    blox_shrink_by(TYPE, (buffer), amount);        \
  } while (0)

#define blox_shift(TYPE, buffer) blox_shift_by(TYPE, buffer, 1)

#define blox_unshift(TYPE, buffer, value)             \
  do {                                                \
    size_t length = (buffer).length;                  \
    blox_resize(TYPE, (buffer), length + 1);          \
    TYPE* begin = blox_begin(TYPE, buffer);           \
    memmove(begin + 1, begin, length * sizeof(TYPE)); \
    blox_set(TYPE, (buffer), 0, value);               \
  } while (0)

#define blox_unshift_by(TYPE, buffer, amount)              \
  do {                                                     \
    size_t length = (buffer).length;                       \
    blox_resize(TYPE, (buffer), length + amount);          \
    TYPE* begin = blox_begin(TYPE, buffer);                \
    memmove(begin + amount, begin, length * sizeof(TYPE)); \
    blox_clear_at(TYPE, (buffer), 0, amount);              \
  } while (0)

#define blox_append(TYPE, buffer, other)                     \
  do {                                                       \
    size_t length = (buffer).length;                         \
    size_t additional = (other).length;                      \
    blox_resize(TYPE, (buffer), length + additional);        \
    memcpy(blox_index(TYPE, (buffer), length), (other).data, \
           additional * sizeof(TYPE));                       \
  } while (0)

#define blox_append_sequence(TYPE, buffer, start, end) \
  blox_append(TYPE, buffer, blox_use_sequence(TYPE, start, end))

#define blox_append_array(TYPE, buffer, array, length) \
  blox_append(TYPE, buffer, blox_use_array(TYPE, array, length))

#define blox_append_string(TYPE, buffer, array) \
  blox_append(TYPE, buffer, blox_use_string(TYPE, array))

#define blox_splice(TYPE, buffer, index, other)                          \
  do {                                                                   \
    size_t length = (buffer).length;                                     \
    size_t additional = (other).length;                                  \
    blox_resize(TYPE, (buffer), length + additional);                    \
    TYPE* begin = blox_index(TYPE, buffer, index);                       \
    memmove(begin + additional, begin, (length - index) * sizeof(TYPE)); \
    memcpy(begin, (other).data, additional * sizeof(TYPE));              \
  } while (0)

#define blox_splice_sequence(TYPE, buffer, index, start, end) \
  blox_splice(TYPE, buffer, index, blox_use_sequence(TYPE, start, end))

#define blox_splice_array(TYPE, buffer, index, array, length) \
  blox_splice(TYPE, buffer, index, blox_use_array(TYPE, array, length))

#define blox_splice_string(TYPE, buffer, index, array) \
  blox_splice(TYPE, buffer, index, blox_use_string(TYPE, array))

#define blox_prepend(TYPE, buffer, other) blox_splice(TYPE, buffer, 0, other)

#define blox_prepend_sequence(TYPE, buffer, start, end) \
  blox_prepend(TYPE, buffer, blox_use_sequence(TYPE, start, end))

#define blox_prepend_string(TYPE, buffer, array) \
  blox_prepend(TYPE, buffer, blox_use_string(TYPE, array))

#define blox_prepend_array(TYPE, buffer, array, length) \
  blox_prepend_array(TYPE, buffer, blox_use_array(TYPE, array, length))

#define blox_copy(TYPE, buffer, source)    \
  do {                                     \
    blox_shrink(TYPE, buffer);                   \
    blox_append(TYPE, (buffer), (source)); \
  } while (0)

#define blox_clone(TYPE, buffer) \
  blox_clone_(sizeof(TYPE), (buffer).data, (buffer).length)

#define blox_swap(buffer, other) \
  do {                           \
    blox stored = (buffer);      \
    (buffer) = (other);          \
    (other) = stored;            \
  } while (0)

#define blox_reverse(TYPE, buffer)         \
  do {                                     \
    TYPE* left = blox_begin(TYPE, buffer); \
    TYPE* right = blox_end(TYPE, buffer);  \
    TYPE swap;                             \
    while (left < --right) {               \
      swap = *left;                        \
      *left++ = *right;                    \
      *right = swap;                       \
    }                                      \
  } while (0)

#define blox_free(buffer) \
  do {                    \
    blox_realloc(NULL)((buffer).data, 0);  \
    blox_drop(buffer);    \
  } while (0)

#define blox_offset(TYPE, buffer, pointer) \
  blox__safe_subtract((TYPE*)pointer, (TYPE*)(buffer).data)

#define blox_for_each(TYPE, buffer, action)                                   \
  do {                                                                        \
    typedef void (*callback)(const void*, size_t);                            \
    callback step = (callback)action;                                         \
    for (size_t index = 0, length = (buffer).length; index < length; ++index) \
      step(blox_index(TYPE, buffer, index), index);                           \
  } while (0)

#define blox_visit(TYPE, buffer, action, userdata)                            \
  do {                                                                        \
    typedef void (*callback)(const void*, void*);                             \
    callback step = (callback)action;                                         \
    for (size_t index = 0, length = (buffer).length; index < length; ++index) \
      step(blox_index(TYPE, buffer, index), userdata);                        \
  } while (0)

blox blox_make_(size_t width, size_t length, int reserved) {
  blox buffer = {0};
  size_t size = length * width;
  if (reserved)
    blox_reserve(char, buffer, size);
  else
    blox_resize(char, buffer, size);
  buffer.length /= width;
  buffer.capacity /= width;
  return buffer;
}

blox blox_clone_(size_t width, const void* data, size_t length) {
  size_t size = length * width;
  blox buffer = blox_make(char, size);
  memcpy(buffer.data, data, size);
  buffer.length = length;
  buffer.capacity /= width;
  return buffer;
}

blox blox_use_string_(size_t width, const void* data) {
  typedef unsigned char byte;
  byte* base = ((byte*)data);
  byte* current = base;
  for (;;) {
    size_t count = width;
    do {
      if (*current != 0) {
        current += count;
        break;
      } else
        ++current;
    } while (--count);
    if (count == 0)
      break;
  }
  size_t length = ((current - base) / width) - 1;
  blox buffer = {base, length, length};
  return buffer;
}

typedef int (*blox_comparison)(const void*, const void*);

#define blox_sort(TYPE, buffer, comparison)           \
  qsort((buffer).data, (buffer).length, sizeof(TYPE), \
        (blox_comparison)comparison)

void* blox_find_(void* key,
                 void* buffer,
                 size_t length,
                 size_t width,
                 blox_comparison comparison) {
  typedef unsigned char byte;
  byte* current = (byte*)buffer;
  while (length--) {
    if (comparison(key, current) == 0)
      return current;
    current += width;
  }
  return NULL;
}

#define blox_find(TYPE, buffer, key, comparison)                         \
  ((TYPE*)blox_find_(&key, (buffer).data, (buffer).length, sizeof(TYPE), \
                     (blox_comparison)comparison))

#define blox_search(TYPE, buffer, key, comparison)                    \
  ((TYPE*)bsearch(&key, (buffer).data, (buffer).length, sizeof(TYPE), \
                  (blox_comparison)comparison))

/*
 FIXME: Not entirely rigorous
*/
int blox_compare_(void* lhs, size_t lmx, void* rhs, size_t rmx, size_t width) {
  if (lmx != rmx)
    return lmx < rmx ? -1 : 1;
  return memcmp(lhs, rhs, lmx * width);
}

#define blox_compare(TYPE, lbx, rbx)                                \
  blox_compare_((lbx).data, (lbx).length, (rbx).data, (rbx).length, \
                sizeof(TYPE))

#define blox_equal(TYPE, lbx, rbx) (blox_compare(TYPE, lbx, rbx) == 0)

#define blox_less(TYPE, lbx, rbx) (blox_compare(TYPE, lbx, rbx) < 0)

#define blox_less_or_equal(TYPE, lbx, rbx) (blox_compare(TYPE, lbx, rbx) <= 0)

#define blox_greater(TYPE, lbx, rbx) (blox_compare(TYPE, lbx, rbx) > 0)

#define blox_greater_or_equal(TYPE, lbx, rbx) \
  (blox_compare(TYPE, lbx, rbx) >= 0)

#endif  // BLOX_H_INCLUDED
