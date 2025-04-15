#define ARRAYLIST_TYPES \
	X(int, int) \
	X(float, float) \
	X(string, char*) \


#define ARRAYLIST_IMPL
#include "arraylist.h"

#include <assert.h>

int main() {

	int *numbers = arraylist_int_create(1);
	numbers = arraylist_int_append(numbers, 0);
	numbers = arraylist_int_append(numbers, 1);
	numbers = arraylist_int_append(numbers, 2);
	numbers = arraylist_int_append(numbers, 3);
	numbers = arraylist_int_append(numbers, 4);
	assert(arraylist_int_size(numbers) == 5);
	assert(arraylist_int_capacity(numbers) == 8);
	for (size_t i = 0; i < arraylist_int_size(numbers); i++) {
		assert(numbers[i] == i);
	}
	arraylist_int_wipe(numbers);
	assert(arraylist_int_size(numbers) == 0);
	arraylist_int_destroy(numbers);

	float *floats = arraylist_float_create(16);
	floats = arraylist_float_append(floats, 0.0f);
	floats = arraylist_float_append(floats, 1.0f);
	floats = arraylist_float_append(floats, 2.0f);
	floats = arraylist_float_append(floats, 3.0f);
	floats = arraylist_float_append(floats, 4.0f);
	assert(arraylist_float_size(floats) == 5);
	assert(arraylist_float_capacity(floats) == 16);
	for (size_t i = 0; i < arraylist_float_size(floats); i++) {
		assert(floats[i] == (float) i);
	}
	arraylist_float_wipe(floats);
	assert(arraylist_float_size(floats) == 0);
	arraylist_float_destroy(floats);

	char **strings = arraylist_string_create(16);
	strings = arraylist_string_append(strings, (char*) 0);
	strings = arraylist_string_append(strings, (char*) 1);
	strings = arraylist_string_append(strings, (char*) 2);
	strings = arraylist_string_append(strings, (char*) 3);
	strings = arraylist_string_append(strings, (char*) 4);
	assert(arraylist_string_size(strings) == 5);
	assert(arraylist_string_capacity(strings) == 16);
	for (size_t i = 0; i < arraylist_string_size(strings); i++) {
		assert(strings[i] == (char*) i);
	}
	arraylist_string_wipe(strings);
	assert(arraylist_string_size(strings) == 0);
	arraylist_string_destroy(strings);

	// testing pop
	numbers = arraylist_int_create(1);
	numbers = arraylist_int_append(numbers, 0);
	numbers = arraylist_int_append(numbers, 1);
	numbers = arraylist_int_append(numbers, 2);
	numbers = arraylist_int_append(numbers, 3);
	numbers = arraylist_int_append(numbers, 4);

	assert(arraylist_int_pop(numbers) == 4);
	assert(arraylist_int_pop(numbers) == 3);
	assert(arraylist_int_pop(numbers) == 2);
	assert(arraylist_int_pop(numbers) == 1);
	assert(arraylist_int_pop(numbers) == 0);

	arraylist_int_destroy(numbers);

	return 0;
}
