#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TAM_INICIAL 50


typedef struct heap{
    void** vector;
    cmp_func_t cmp;
    size_t tam;
    size_t cantidad;
} heap_t;




heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap_nuevo = malloc(sizeof(heap_t));
    if(heap_nuevo == NULL){
        return NULL;
    }
    void** vector_nuevo = malloc(sizeof(void*)*TAM_INICIAL);
    if(vector_nuevo == NULL){
        free(heap_nuevo);
        return NULL;
    }
    heap_nuevo->cantidad = 0;
    heap_nuevo->tam = TAM_INICIAL;
    heap_nuevo->cmp = cmp;
    heap_nuevo->vector = vector_nuevo;
    return heap_nuevo;
}



size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}


bool heap_esta_vacio(const heap_t *heap){
    return(heap->cantidad == 0);
}
