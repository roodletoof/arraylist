#ifndef ARRAYLIST_HEADER
#define ARRAYLIST_HEADER

#include <stddef.h>

#ifndef ARRAYLIST_TYPES
#define ARRAYLIST_TYPES \
	X(int, int) \
	X(uint, unsigned int) \
	X(char, char) \
	X(uchar, unsigned char) \
	X(long, long) \
	X(ulong, unsigned long) \
	X(longlong, long long) \
	X(ulonglong, unsigned long long) \
	X(float, float) \
	X(double, double) \
	X(intptr, int*) \
	X(uintptr, unsigned int*) \
	X(charptr, char*) \
	X(ucharptr, unsigned char*) \
	X(longptr, long*) \
	X(ulongptr, unsigned long*) \
	X(longlongptr, long long*) \
	X(ulonglongptr, unsigned long long*) \
	X(floatptr, float*) \
	X(doubleptr, double*)

#endif

#define X(NAME, TYPE) \
	TYPE *arraylist_##NAME##_create(size_t initial_capacity); \
	void arraylist_##NAME##_destroy(TYPE *this); \
	TYPE *arraylist_##NAME##_append(TYPE *this, TYPE value); \
	size_t arraylist_##NAME##_size(TYPE *this); \
	size_t arraylist_##NAME##_capacity(TYPE *this); \
	void arraylist_##NAME##_wipe(TYPE *this);

	
ARRAYLIST_TYPES
#undef X

#ifdef ARRAYLIST_IMPL

#include <stdlib.h>
#include <assert.h>

#define CONTAINER(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))


#define X(NAME, TYPE) \
	typedef struct header_##NAME { \
		size_t size, capacity; \
		TYPE values[]; \
	} header_##NAME##_t; \
 \
	TYPE *arraylist_##NAME##_create(size_t initial_capacity) { \
		assert(initial_capacity != 0); \
		header_##NAME##_t *header = malloc(sizeof(header_##NAME##_t) + sizeof(TYPE) * initial_capacity); \
		assert(header != NULL); \
		header->size = 0; \
		header->capacity = initial_capacity; \
		return header->values; \
	} \
 \
	void arraylist_##NAME##_destroy(TYPE *this) { \
		header_##NAME##_t *header = CONTAINER(this, header_##NAME##_t, values); \
		free(header); \
	} \
 \
	TYPE *arraylist_##NAME##_append(TYPE *this, TYPE value) { \
		header_##NAME##_t *header = CONTAINER(this, header_##NAME##_t, values); \
		if (header->size >= header->capacity) { \
			size_t new_capacity = header->capacity * 2; \
			header = realloc(header, sizeof(*header) + sizeof(TYPE) * new_capacity); \
			assert(header != NULL); \
			header->capacity = new_capacity; \
		} \
		header->values[header->size++] = value; \
		return header->values; \
	} \
 \
	size_t arraylist_##NAME##_size(TYPE *this) { \
		header_##NAME##_t *header = CONTAINER(this, header_##NAME##_t, values); \
		return header->size; \
	} \
 \
	size_t arraylist_##NAME##_capacity(TYPE *this) { \
		header_##NAME##_t *header = CONTAINER(this, header_##NAME##_t, values); \
		return header->capacity; \
	} \
	void arraylist_##NAME##_wipe(TYPE *this) { \
		header_##NAME##_t *header = CONTAINER(this, header_##NAME##_t, values); \
		header->size = 0; \
	}

ARRAYLIST_TYPES
#undef X


#undef CONTAINER
#endif /* ARRAYLIST_IMPL */
#endif /* ARRAYLIST_HEADER */
