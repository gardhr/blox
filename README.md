# blox

Blox is single-header array library for C, implemented as a set of macros. 

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

`blox blox_nil(void)`

Returns a nil blox

<br>

`void blox_free(buffer)`

Frees a blox container (don't forget!)

<br>

`void blox_drop(buffer)`

Zeroes out the container, but doesn't free it (use with care!)

<br>

`blox blox_create(TYPE)`

Returns a blox with zero elements (must be freed with `blox_free`)

<br>

`blox blox_make(TYPE, length)`

Returns a blox with `length` elements, all zeroed out (must be freed with `blox_free`)

<br>

`blox blox_reserved(TYPE, length)`

Returns a blox with `length` elements reserved; nominal size of container will be zero  (must be freed with `blox_free`)

<br>

`blox blox_from_array(TYPE, array, length)`

Constructs a new blox containing a copy of `array` (must be freed with `blox_free`)

<br>

`blox blox_from_string(TYPE, string)`

Constructs a new blox from a zero-terminated `string` of `TYPE` (must be freed with `blox_free`)

<br>

`blox blox_from_sequence(TYPE, start, end)`

Constructs a new blox object by copying pointer ranges `start` to `end` (must be freed with `blox_free`)

<br>

`blox blox_slice(TYPE, other, start, amount)`

Constructs a new blox object by copying `amount` elements of blox `other` starting from index `start` (must be freed with `blox_free`)

<br>

`blox blox_slice_range(TYPE, other, start, end)`

Constructs a new blox object by copying from index `start` to `end` of blox `other` (must be freed with `blox_free`)

<br>

`blox blox_slice_end(TYPE, other, start)`

Constructs a new blox object by copying the last elements of blox `other` starting at index `start` (must be freed with `blox_free`)

<br>

`blox blox_slice_first(TYPE, other, amount)`

Constructs a new blox object by copying the first `amount` elements of blox `other` (must be freed with `blox_free`)

<br>

`blox blox_slice_last(TYPE, other, amount)`

Constructs a new blox object by copying the last `amount` elements of blox `other` (must be freed with `blox_free`)

<br>

`blox blox_use(array, length)`

Use `array` as if it were a normal blox object (must ***not*** be freed with `blox_free`)

<br>

`blox blox_use_array(TYPE, array, length)`

Use `array` as if it were a normal blox object (must ***not*** be freed with `blox_free`)

<br>

`blox blox_use_string(TYPE, string)`

Use a zero-terminated `string` of `TYPE` as if it were a normal blox object (must ***not*** be freed with `blox_free`)

<br>

`blox blox_use_sequence(TYPE, start, end)`

Use a sequence (from pointer `start` to `end`) as if it were a normal blox object (must ***not*** be freed with `blox_free`)

<br>

`blox blox_use_window(TYPE, other, start, end)`

Use a subsequence (from index `start` to `end`) of blox object `other` as if it were itself a normal blox object (must ***not*** be freed with `blox_free`)

<br>

`blox blox_use_view(TYPE, other, start, amount)`

Use `amount` elements (starting from index `start`) of blox object `other` as if it were itself a normal blox object (must ***not*** be freed with `blox_free`)

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

`TYPE* blox_begin(TYPE, buffer)`

Returns a pointer to the first element in the container

<br>

`TYPE* blox_end(TYPE, buffer)`

Returns a pointer to the unused element *immediately following* the last element in the container

<br>

`TYPE* blox_top(TYPE, buffer)`

Returns a pointer to the last element in the container

<br>

`TYPE* blox_bottom(TYPE, buffer)`

Returns a pointer to the unused element *immediately preceding* the first element in the container

<br>

`TYPE blox_front(TYPE, buffer)`

Returns a reference to the first element in the container

<br>

`TYPE blox_back(TYPE, buffer)`

Returns a reference to the last element in the container

<br>

`void blox_resize(TYPE, buffer, length)`

Resizes the container (and `buffer.length` is set to `length`)

<br>

`void blox_reserve(TYPE, buffer, length)`

Reserves `length` elements (`buffer.length` remains unchanged)

<br>

`void blox_shrink(TYPE, buffer)`

Resizes the container to zero elements

<br>

`void blox_shrink_by(TYPE, buffer, amount)`

Shrinks the container by `amount` elements

<br>

`bool blox_empty(buffer)`

Returns `true` if the blox is empty (`buffer.length == 0`)

<br>

`void blox_clear_range(TYPE, buffer, start, end)`

Zeroes out all elements from index `start` up to (but excluding) `end` (the container is ***not*** resized)

<br>

`void blox_clear_at(TYPE, buffer, start, amount)`

Zeroes out `amount` elements starting from index `start` (the container is ***not*** resized)

<br>

`void blox_clear_end(TYPE, buffer, start)`

Zeroes out all elements from index `start` up to the last element (the container is ***not*** resized)

<br>

`void blox_clear(TYPE, buffer)`

Zeroes out all elements (the container is ***not*** resized)

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

`void blox_shift_by(TYPE, buffer, amount)`

Removes the first `amount` elements from the front of the container

<br>

`void blox_shift(TYPE, buffer)`

Removes the first element of the container

<br>

`void blox_unshift(TYPE, buffer, value)`

Inserts `value` at the front of the container (remaining elements are shifted toward the back)

<br>

`void blox_unshift_by(TYPE, buffer, amount)`

Makes space at the front of the container for `amount` (zeroed out) elements (remaining elements are shifted toward the back)

<br>

`void blox_erase_range(TYPE, buffer, start, end)`

Removes all elements from index `start` up to (but excluding) `end`

<br>

`void blox_erase_at(TYPE, buffer, start, amount)`

Removes `amount` elements starting from index `start`

<br>

`void blox_erase(TYPE, buffer, index)`

Erases the element at `index`

<br>

`void blox_reverse(TYPE, buffer)`

Reverses the elements in `buffer` (inplace)

<br>

`void blox_splice(TYPE, buffer, index, other)`

Splices blox `other` to `buffer` at `index`

<br>

`void blox_splice_sequence(TYPE, buffer, index, start, end)`

Splices the sequence from pointer `start` to `end` to the container `buffer` at `index`

<br>

`void blox_splice_string(TYPE, buffer, index, string)`

Splices a zero-terminated `string` of `TYPE` to the container `buffer` at `index`

<br>

`void blox_splice_array(TYPE, buffer, index, array, length)`

Splices `length` elements of `array` to the container `buffer` at `index`

<br>

`void blox_append(TYPE, buffer, other)`

Appends the blox `other` to `buffer`

<br>

`void blox_append_sequence(TYPE, buffer, start, end)`

Appends the sequence from pointer `start` to `end` to the container

<br>

`void blox_append_string(TYPE, buffer, string)`

Appends a zero-terminated `string` of `TYPE` to the container

<br>

`void blox_append_array(TYPE, buffer, array, length)`

Appends `length` elements of `array` to the container

<br>

`void blox_prepend(TYPE, buffer, other)`

Prepends the blox `other` to `buffer`

<br>

`void blox_prepend_sequence(TYPE, buffer, start, end)`

Prepends the sequence from pointer `start` to `end` to the container

<br>

`void blox_prepend_string(TYPE, buffer, string)`

Prepends a zero-terminated `string` of `TYPE` to the container

<br>

`void blox_prepend_array(TYPE, buffer, array, length)`

Prepends `length` elements of `array` to the container

<br>

`void blox_copy(TYPE, buffer, source)`

Copies `source` to `buffer`

<br>

`blox blox_clone(TYPE, buffer)`

Returns a copy of `buffer`

<br>

`void blox_swap(buffer, other)`

Swaps `buffer` with `other`

<br>

`void blox_for_each(TYPE, buffer, action)`

Applies `action` to each element of `buffer` (function should take a `TYPE*` as it's first argument, plus an optional `size_t` argument for the index)

<br>

`void blox_visit(TYPE, buffer, action, userdata)`

Applies `action` to each element of `buffer` (function should take a `TYPE*` as it's first argument, plus an optional `void*` argument for `userdata`)

<br>

`void blox_sort(TYPE, buffer, compare)`

Sort using `compare`, which should take two arguments of type `TYPE*`

<br>

`TYPE* blox_search(TYPE, buffer, key, compare)`

Binary search using `compare`, which should take two arguments of type `TYPE*`

<br>

`TYPE* blox_find(TYPE, buffer, key, compare)`

Sequential search using `compare`, which should take two arguments of type `TYPE*`

<br>

`int blox_compare(TYPE, left, right)`

Compares two blox containers (first compares lengths; if equal, a bit-by-bit comparison of the two is made)

<br>

`bool blox_equal(TYPE, left, right)`

Returns true if `left` and `right` compare equal

<br>

`bool blox_less(TYPE, left, right)`

Returns true if `left` compares less than `right`

<br>

`bool blox_less_or_equal(TYPE, left, right)`

Returns true if `left` compares less or equal to `right`

<br>

`bool blox_greater(TYPE, left, right)`

Returns true if `left` compares greater than `right`

<br>

`bool blox_greater_or_equal(TYPE, left, right)`

Returns true if `left` compares greater than or equal to `right`

<br>

`typedef void* (*blox_allocator)(void*, size_t)`

<br>

`blox_allocator blox_realloc(blox_allocator reset)`

Sets the default allocator for all blox objects (must have the same interface as `realloc`)

<br>



