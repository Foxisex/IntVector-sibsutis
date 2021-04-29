#include "IntVector.h"
#include <string.h>
#include <stdlib.h>

IntVector *int_vector_new(size_t initial_capacity)
{
    if (initial_capacity >= 0) {
        IntVector *v = malloc(sizeof(IntVector));
        if (v == NULL) {
            return NULL;
        }
        v->data = malloc(sizeof(int) * initial_capacity);
        if (v->data == NULL) {
            free(v);
            return NULL;
        }
        v->size = 0;
        v->capacity = initial_capacity;
        return v;
    } else {
        return NULL;
    }
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *t = malloc(sizeof(IntVector));
	if (t == NULL) {
		return NULL;
	}
	t->data = malloc(sizeof(int) * int_vector_get_capacity(v));
	if (t->data == NULL) {
		free(t);
		return NULL;
	}
	memcpy(t->data, v->data, sizeof(int) * int_vector_get_capacity(v));
	t->size = int_vector_get_size(v);
	t->capacity = int_vector_get_capacity(v);
	return t;
}

void int_vector_free(IntVector *v)
{
	if (v) {
		free(v->data);
		free(v);
	}
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	if ((index >= 0) && (index < int_vector_get_capacity(v))) {
		return v->data[index];
		return 0;
	}
	else { return -1; }
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	if ((index >= 0) && (index < int_vector_get_capacity(v))) {
		v->data[index] = item;
	}
}

size_t int_vector_get_size(const IntVector *v)
{
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	if (int_vector_get_capacity(v) == 0){
		v->capacity = 1;
	}
	if (int_vector_get_capacity(v) == int_vector_get_size(v)) {
		int *t = realloc(v->data, sizeof(int) * int_vector_get_capacity(v) * 2);
		if (t == NULL) {
			return -1;
		}
		v->capacity *= 2;
		v->data = t;
	}
	v->data[int_vector_get_size(v)] = item;
	v->size++;

	return 0;
}

void int_vector_pop_back(IntVector *v)
{
	if (int_vector_get_size(v) != 0) {
		v->size--;
	}
}

int int_vector_shrink_to_fit(IntVector *v)
{
	if (int_vector_get_capacity(v) > int_vector_get_size(v)) {
		int *t = realloc(v->data, sizeof(int) * int_vector_get_size(v));
		if (t == NULL) {
			return -1;
		}
		v->data = t;
	}
	v->capacity = int_vector_get_size(v);
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
    if (new_size >= 0) {
        if (new_size > int_vector_get_size(v)) {
            for (int i = int_vector_get_size(v); i < new_size; i++) {
                if (int_vector_push_back(v, 0) == -1) {
                    return -1;
                }
            }
        }
        v->size = new_size;
        return 0;
    } else {
        return -1;
    }
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
    if (new_capacity >= 0) {
        if (new_capacity > v->capacity) {	
            v->capacity = new_capacity;
            int *t = realloc(v->data, sizeof(int) * v->capacity);
            if (t == NULL) {
                return -1;
            }
            v->data = t;
        }
        return 0;
    } else {
        return -1;
    }
}
