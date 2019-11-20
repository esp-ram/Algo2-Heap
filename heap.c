#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#define TAM_INICIAL 50
#define FACTOR_REDIM 2
#define CONDICION_DISMINUCION 4


struct heap{
    void** vector;
    cmp_func_t cmp;
    size_t tam;
    size_t cantidad;
};

////////////////Funciones Auxiliares

size_t posicion_hijo_izq(size_t padre){
    return((padre*2) + 1);
}

size_t posicion_hijo_der(size_t padre){
    return((padre*2) +2);
}

size_t posicion_padre(size_t hijo){
    return((hijo-1) / 2);
}


void swap(void** vector, size_t elem1, size_t elem2){
    void* aux = vector[elem1];
    vector[elem1] = vector[elem2];
    vector[elem2] = aux;
}


size_t hijo_mayor(void** vector, size_t posicionPadre, size_t maximo, cmp_func_t cmp){
    size_t posHijoIzq = posicion_hijo_izq(posicionPadre);
    size_t posHijoDer = posicion_hijo_der(posicionPadre);

    if(posHijoIzq >= maximo){
        return 0;
    }else if (posHijoDer >= maximo){
        return posHijoIzq;
    }
    void* hijoIzq = vector[posHijoIzq];
    void* hijoDer = vector[posHijoDer];
    if(cmp(hijoIzq,hijoDer) < 0){
        return posHijoDer;
    }
    return posHijoIzq;
}


void upheap(heap_t* heap, size_t posicion){
    if(heap->cantidad == 1 || posicion == 0){
        return;
    }
    size_t posicionPadre = posicion_padre(posicion);
    void* hijo = heap->vector[posicion];
    void* padre = heap->vector[posicionPadre];
    if(heap->cmp(hijo,padre) <= 0){
        return;
    }
    swap(heap->vector,posicion,posicionPadre);
    upheap(heap,posicionPadre);
}


void downheap_aux(void** vector, size_t posicion, cmp_func_t cmp, size_t cantidad){

    size_t posHijoMayor = hijo_mayor(vector, posicion, cantidad, cmp);
    if(posHijoMayor == 0){ //si no tiene hijos
        return;
    }
    void* padre = vector[posicion];
    void* hijoMayor = vector[posHijoMayor];
    if(cmp(padre,hijoMayor) >= 0){
        return;
    }
    swap(vector,posicion, posHijoMayor);
    downheap_aux(vector, posHijoMayor, cmp, cantidad);
}


void downheap(heap_t* heap, size_t posicion){
    downheap_aux(heap->vector, posicion, heap->cmp, heap->cantidad);
}


void heapify(void* vector, size_t n, cmp_func_t cmp){
    size_t medio = (n / 2);
    for(size_t i = medio; i>0; i--){
        downheap_aux(vector, i-1, cmp, n);
    }
}


bool vector_redimensionar(heap_t* heap, size_t tamNuevo) {
    void** datosNuevos = realloc(heap->vector, tamNuevo * sizeof(void*));
    if(datosNuevos == NULL) {
        return false;
    }
    heap->vector = datosNuevos;
    heap->tam = tamNuevo;
    return true;
}

///////////////////Primitivas

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heapNuevo = malloc(sizeof(heap_t));
    if(heapNuevo == NULL){
        return NULL;
    }
    void** vectorNuevo = malloc(sizeof(void*)*n);
    if(vectorNuevo == NULL){
        free(heapNuevo);
        return NULL;
    }
    for(int i = 0; i<n; i++){
        vectorNuevo[i] = arreglo[i];
    }
    heapNuevo->cantidad = n;
    heapNuevo->tam = n;
    heapNuevo->cmp = cmp;
    heapify(vectorNuevo,n,cmp);
    heapNuevo->vector = vectorNuevo;
    return heapNuevo;
}


heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heapNuevo = malloc(sizeof(heap_t));
    if(heapNuevo == NULL){
        return NULL;
    }
    void** vectorNuevo = malloc(sizeof(void*)*TAM_INICIAL);
    if(vectorNuevo == NULL){
        free(heapNuevo);
        return NULL;
    }
    heapNuevo->cantidad = 0;
    heapNuevo->tam = TAM_INICIAL;
    heapNuevo->cmp = cmp;
    heapNuevo->vector = vectorNuevo;
    return heapNuevo;
}



size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}


bool heap_esta_vacio(const heap_t *heap){
    return(heap->cantidad == 0);
}


void *heap_ver_max(const heap_t *heap){
    if(heap_esta_vacio(heap)){
        return NULL;
    }
    return (heap->vector[0]);
}


bool heap_encolar(heap_t *heap, void *elem){
    if(elem == NULL){
        return false;
    }
    if (heap->cantidad >= heap->tam -1){
        if(vector_redimensionar(heap,heap->tam * FACTOR_REDIM) == false){
            return false;
        }
    }
    heap->vector[heap->cantidad] = elem;
    heap->cantidad += 1;
    upheap(heap,heap->cantidad-1);
    return true;
}


void* heap_desencolar(heap_t *heap){
    if(heap->cantidad == 0){
        return NULL;
    }
    void* datoDevolver = heap->vector[0];

    swap(heap->vector,0,heap->cantidad-1);
    heap->cantidad -= 1;
    heap->vector[heap->cantidad] = NULL;
    downheap(heap,0);

    if ((heap->cantidad * CONDICION_DISMINUCION <= heap->tam) && (heap->cantidad > TAM_INICIAL)){
        if (vector_redimensionar(heap,heap->tam / FACTOR_REDIM)){
        }
    }

    return datoDevolver;
}


void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if (destruir_elemento != NULL){
        for(int i = 0; i < heap->cantidad; i++){
            destruir_elemento(heap->vector[i]);
        }
    }
    free(heap->vector);
    free(heap);
}

///////////////////////HeapSort

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos,cant,cmp);

    for(int i = 1; i < cant; i++){
        swap(elementos,0,cant-i);
        downheap_aux(elementos, 0, cmp, cant-i);
    }
}
