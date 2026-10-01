#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"

void dv_init( dbl_vector_t* vec ) {
    vec->data = malloc(DV_INITIAL_CAPACITY * sizeof(double));
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
}

void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {

    if (new_size > vec->capacity) {
        vec->capacity = fmax(vec->capacity * DV_GROWTH_FACTOR, new_size);
        vec->data = realloc(vec->data,vec->capacity * sizeof(double));
    }

}


void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
    vec->data = NULL;
}

void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    dest->size = vec->size;
    dv_ensure_capacity(dest,vec->size);
    for (size_t i = 0; i < vec->size; i++ ) {
        dest->data[i] = vec->data[i];    
    }
}

void dv_clear( dbl_vector_t* vec ) {
    vec->size = 0;
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    size_t new = vec->data+=1;
    dv_ensure_capacity(vec, new);
    vec->data[vec->size] = new_item;
    new = vec->size;
}

void dv_pop( dbl_vector_t* vec ) {
    if (vec->size <= 0) {
        vec->size = 0;
    }
    else { vec->size-=1; }
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    if (vec->size > 0) {
        result = vec->data[vec->size - 1];
    }
    return result;
}

void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    size_t loc = fmin(pos, vec->size);

    vec->size += 1;
    dv_ensure_capacity(vec, vec->size);

    for (size_t i = vec->size - 1; i > loc; i--) {
        vec->data[i] = vec->data[i - 1];
    }

    vec->data[loc] = new_item;

}

void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    size_t loc = fmin(pos, vec->size);
    if (pos < vec->size) {
        vec->size -= 1;
        for (size_t i = loc; i <= vec->size; i++) {
            vec->data[i] = vec->data[i + 1];
        }
    }
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    for (size_t i = 0; i <= vec->size; i++) {
        callback(vec->data[i], info);
    }
}