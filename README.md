# How to use

```c

// Only put this define in ONE c file.
#define ARRAYLIST_IMPL
#include "arraylist.h" // or include your wrapper (see "Customize the supported types")

void main() {
    // Give the initial capacity of the arraylist, which must be larger than 0.
    int *nums = arraylist_int_create(1);

    // Append to the list similar to how you would in golang.
    nums = arraylist_int_append(nums, 420);

    // Access the values with normal array syntax
    printf("The first number is: %d", nums[0]);

    // Get the size and capacity
    size_t size, capacity;
    size = arraylist_int_size(nums);
    capacity = arraylist_int_capacity(nums);

    // Wipe the list by resetting the internal size member to 0 with O(1) time complexity.
    arraylist_int_wipe(nums);

    // Remember to destroy the list to avoid memory leaks
    arraylist_int_destroy(nums);
}
```
# Customize the supported types
create a wrapper header file that defines the ARRAYLIST\_TYPES X-macro like this:

```c
// The first parameter is the name. E.g. arraylist_[name]_create.
// The second is the type of the arraylist.
#define ARRAYLIST_TYPES \
	X(int, int) \
	X(uint, unsigned int) \
	X(string, char*)

#include "arraylist.h"
```
Anywhere you would have included arraylist.h, include your wrapper file instead.

# Details
The functions will assert that memory has been allocated successfully and that
they are being called correctly.
