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

`void blox_drop(buffer)`

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

`blox_sort(TYPE, buffer, compare)`

`blox_search(TYPE, buffer, key, compare)`

