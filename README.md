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

`TYPE* blox_data(TYPE, buffer)`

Returns a pointer to the first element (typecast of `buffer.data`)

<br>

`size_t blox_length(buffer)`

Returns the number of elements (same as `buffer.length`)

<br>

`size_t blox_capacity(buffer)`

Returns the number of elements reserved by the container (same as `buffer.capacity`)

<br>

`bool blox_empty(buffer)`

Returns `true` if the blox is empty (`buffer.length == 0`)

<br>

`blox blox_nil(void)`

Returns a nil blox

<br>

`blox blox_create(TYPE)`

Returns a blox with zero elements

<br>

`blox blox_make(TYPE, length)`

Returns a blox with `length` elements (all zeroed out)

<br>

`void blox_resize(TYPE, buffer, size)`

Resizes the container

<br>

`void blox_shrink(TYPE, buffer)`

Resizes the container to zero elements

<br>

`void blox_free(buffer)`

Frees a blox container

<br>

`void blox_drop(buffer)`

Zeroes out the container, but doesn't free it (use with care!)

<br>

`TYPE* blox_index(TYPE, buffer, index)`

Returns a pointer to the element at `index`

<br>

`TYPE blox_get(TYPE, buffer, index)`

Returns a reference to the element at `index` (not bounds checked!)

<br>

`void blox_set(TYPE, buffer, index, value)`

Sets the element at `index` to `value` (not bounds checked!)

<br>

`void blox_clear_range(TYPE, buffer, start, end)`

Zeroes out all elements from index `start` up to (but excluding) `end`

<br>

`void blox_insert(TYPE, buffer, index, value)`

Inserts `value` at `index` of the (possibly empty) container

<br>

`void blox_stuff(TYPE, buffer)`

Inserts a zero-filled object of `TYPE` at the end of the container

<br>

`void blox_push(TYPE, buffer, value)`

Inserts `value` at the end of the container

<br>

`void blox_pop(TYPE, buffer)`

Removes the last element, then shrinks the container by one (if possible)

<br>

`TYPE blox_front(TYPE, buffer)`

Returns a reference to the first element in the container

<br>

`TYPE blox_back(TYPE, buffer)`

Returns a reference to the last element in the container

<br>

`TYPE* blox_begin(TYPE, buffer)`

Returns a pointer to the first element in the container

<br>

`TYPE* blox_end(TYPE, buffer)`

Returns a pointer to the unused element immediately following the last element in the container

<br>

`TYPE* blox_top(TYPE, buffer)`

Returns a pointer to the last element in the container

<br>

`void blox_append(TYPE, buffer, other)`

Appends the blox `other` to `buffer`

<br>

`void blox_append_sequence(TYPE, buffer, start, end)`

Appends the sequence from pointer `start` to `end` to the container

<br>

`void blox_append_string(TYPE, buffer, array)`

Appends a zero-terminated `array` to the container

<br>

`void blox_append_array(TYPE, buffer, array, length)`

Appends `length` elements of `array` to the container

<br>

`void blox_copy(TYPE, buffer, source)`

Copies `source` to `buffer`

<br>

`blox blox_clone(TYPE, buffer)`

Returns a copy of `buffer` (don't forget to clean up with `blox_free(buffer)`!)

<br>

`void blox_swap(buffer, other)`

Swaps `buffer` with `other`

<br>

`void blox_for_each(TYPE, buffer, action)`

Applies `action` to each element of `buffer` (function should take a `TYPE*` as it's first argument, plus an optional `size_t` argument for the index)

<br>

`void blox_sort(TYPE, buffer, compare)`

Sort using `compare`, which should take two arguments of type `TYPE**`

<br>

`void blox_search(TYPE, buffer, key, compare)`

Binary search using `compare`, which should take two arguments of type `TYPE**`

<br>

