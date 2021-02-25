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

`blox blox_nil(void)`

Returns a zero-initialized blox

<br>  

`TYPE* blox_data(TYPE, buffer)`

Returns a pointer to the first element



`TYPE* blox_index(TYPE, buffer, index)`

Returns a pointer to the element at `index`



`TYPE blox_get(TYPE, buffer, index)`

Returns a reference to the element at `index`



`void blox_set(TYPE, buffer, index, value)`

Sets the element at `index` to `value`



`size_t blox_length(buffer)` 

Returns the number of elements



`bool blox_empty(buffer)` 

Returns `true` if the blox is empty



`size_t blox_capacity(buffer)` 

Returns the number of elements reserved by the container



`blox blox_make(TYPE, length)`

Returns a blox with `length` elements (all zeroed out)



`void blox_shrink(buffer)`

Resizes the container to zero elements



`void blox_drop(buffer)`

Zeroes out the container, but doesn't free it (use with care!)



`void blox_clear_range(TYPE, buffer, start, end)`

Zeroes out all elements from index `start` up to (but excluding) `end`



`void blox_insert(TYPE, buffer, index, value)`

Inserts `value` at `index` of the (possibly empty) container



`void blox_resize(TYPE, buffer, size)`

Resizes the container



`void blox_stuff(TYPE, buffer)`

Inserts a zero-filled object of `TYPE` at the end of the container



`void blox_push(TYPE, buffer, value)`

Inserts `value` at the end of the container



`void blox_pop(TYPE, buffer)`

Removes the last element, then shrinks the container by one (if possible)



`TYPE blox_front(TYPE, buffer)`

Returns a reference to the first element in the container



`TYPE blox_back(TYPE, buffer)`

Returns a reference to the last element in the container



`TYPE* blox_begin(TYPE, buffer)`

Returns a pointer to the first element in the container



`TYPE* blox_end(TYPE, buffer)`

Returns a pointer to the unused element immediately following the last element in the container



`TYPE* blox_top(TYPE, buffer)`

Returns a pointer to the last element in the container



`void blox_append(TYPE, buffer, other)`

Appends the blox `other` to `buffer`



`void blox_append_sequence(TYPE, buffer, start, end)`

Appends the sequence from pointer `start` to `end` to the container



`void blox_append_string(TYPE, buffer, array)`

Appends a zero-terminated `array` to the container



`void blox_append_array(TYPE, buffer, array, length)`

Appends `length` elements of `array` to the container



`void blox_copy(TYPE, buffer, source)`

Copies `source` to `buffer`



`blox blox_clone(TYPE, buffer)`

Returns a copy of `buffer`



`void blox_swap(buffer, other)`

Swaps `buffer` with `other`



`void blox_free(buffer)`

Frees a blox container



`void blox_for_each(TYPE, buffer, action)`

Applies `action` to each element of `buffer` (function should take a `TYPE*` as it's first argument, plus an optional `size_t` argument for the index)



`void blox_sort(TYPE, buffer, compare)`

Sort using `compare`, which should take two arguments of type `TYPE**`



`void blox_search(TYPE, buffer, key, compare)`

Binary search using `compare`, which should take two arguments of type `TYPE**`



