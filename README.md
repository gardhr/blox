# blox
Simple array library for C

```
typedef struct
{
 void* data;
 size_t length;
 size_t capacity;
}
 blox;
```

`blox blox_nil()`

`TYPE* blox_data(TYPE, buffer)`

`TYPE* blox_index(TYPE, buffer, index)`

`TYPE blox_get(TYPE, buffer, index)`

`void blox_set(TYPE, buffer, index, value)`

`size_t blox_length(buffer)` 

`bool blox_empty(buffer)` 

`size_t blox_capacity(buffer)` 

`blox blox_make(TYPE, length)`

`void blox_shrink(buffer)`

`void blox_reset(buffer)`

`void blox_clear_range(TYPE, buffer, start, end)`

`void blox_insert(TYPE, buffer, index, value)`

`void blox_resize(TYPE, buffer, size)`

`void blox_stuff(TYPE, buffer)`

`void blox_push(TYPE, buffer, value)`

`void blox_pop(TYPE, buffer)`

`TYPE blox_front(TYPE, buffer)`

`TYPE blox_back(TYPE, buffer)`

`TYPE* blox_begin(TYPE, buffer)`

`TYPE* blox_end(TYPE, buffer)`

`TYPE* blox_top(TYPE, buffer)`

`void blox_append(TYPE, buffer, other)`

`void blox_append_sequence(TYPE, buffer, start, end)`

`void blox_append_string(TYPE, buffer, array)`

`void blox_append_array(TYPE, buffer, array, length)`

`void blox_copy(TYPE, buffer, source)`

`blox blox_clone(TYPE, buffer)`

`void blox_swap(buffer, other)`

`void blox_free(buffer)`

`void blox_for_each(TYPE, buffer, action)`

`typedef int (*blox_compare)(const void*, const void*)`

`blox_sort(TYPE, buffer, compare)`

`blox_search(TYPE, buffer, key, compare)`

`int blox_char_ascending(char* left, char* right)`

`int blox_byte_ascending(unsigned char* left, unsigned char* right)`

`int blox_short_ascending(short* left, short* right)`

`int blox_ushort_ascending(unsigned short* left, unsigned short* right)` 

`int blox_int_ascending(int* left, int* right)`

`int blox_uint_ascending(unsigned int* left, unsigned int* right)`

`int blox_long_ascending(long* left, long* right)`

`int blox_ulong_ascending(unsigned long* left, unsigned long* right)`

`int blox_llong_ascending(long long* left, long long* right)`

`int blox_ullong_ascending(unsigned long long* left, unsigned long long* right)`

`int blox_size_t_ascending(size_t* left, size_t* right)` 

`int blox_float_ascending(float* left, int* right)`

`int blox_double_ascending(double* left, double* right)` 

`int blox_text_ascending(char** left, char** right)`

`int blox_char_descending(char* left, char* right)` 

`int blox_byte_descending(unsigned char* left, unsigned char* right)`

`int blox_short_descending(short* left, short* right)`

`int blox_ushort_descending(unsigned short* left, unsigned short* right)`

`int blox_int_descending(int* left, int* right)` 

`int blox_uint_descending(unsigned int* left, unsigned int* right)`

`int blox_long_descending(long* left, long* right)` 

`int blox_ulong_descending(unsigned long* left, unsigned long* right)` 

`int blox_llong_descending(long long* left, long long* right)`

`int blox_ullong_descending(unsigned long long* left, unsigned long long* right)`

`int blox_size_t_descending(size_t* left, size_t* right)` 

`int blox_float_descending(float* left, int* right)`

`int blox_double_descending(double* left, double* right)` 

`int blox_text_descending(char** left, char** right)`

