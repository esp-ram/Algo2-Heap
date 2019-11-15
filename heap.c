#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TAM_INICIAL 50
#define FACTOR_REDIM 2
#define CONDICION_DISMINUCION 4


typedef struct heap{
    void** vector;
    cmp_func_t cmp;
    size_t tam;
    size_t cantidad;
} heap_t;


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
    vector[elem1] = elem2;
    vector[elem2] = aux;
}


size_t hijo_menor(void* vector, size_t posicionPadre, size_t maximo, cmp_func_t cmp){
    size_t posHijoIzq = posicion_hijo_izq(posicionPadre);
    size_t posHijoDer = posicion_hijo_der(posicionPadre);
    if(posHijoIzq > maximo && posHijoDer > maximo){
        return 0;
    }else if (posHijoIzq > maximo){
        return posHijoDer;
    }else if (posHijoDer > maximo){
        return posHijoIzq;
    }
    void* hijoIzq = vector[posHijoIzq];
    void* hijoDer = vector[posHijoDer];
    if(heap->cmp(hijoIzq,hijoDer) < 0){
        return posHijoIzq;
    }
    return posHijoDer;
}


void upheap(heap_t* heap, size_t posicion){
    size_t posicionPadre = posicion_padre(posicion);
    void* hijo = heap->vector[posicion];
    void* padre = heap->vector[posicionPadre];
    if(heap->cmp(padre,hijo) <= 0){
        return;
    }
    swap(heap->vector,posicion,posHijoMenor);
    upheap(heap,padre);
}


void downheap_aux(void* vector, size_t posicion, cmp_func_t cmp, size_t cantidad){
    size_t posHijoMenor = hijo_menor(vector, posicion, cantidad, cmp);
    if(posHijoMenor == 0){ //si no tiene hijos
        return;
    }
    void* padre = vector[posicion];
    void* hijoMenor = vector[posHijoMenor];
    if(cmp(padre,hijoMenor) <= 0){
        return;
    }
    swap(vector,posicion,posHijoMenor);
    downheap_aux(vector,posHijoMenor,cmp, cantidad);
}


void downheap(heap_t* heap, size_t posicion){
    downheap_aux(heap->vector, posicion, heap->cmp, heap->cantidad);
}


void heapify(void* vector, size_t n, cmp_func_t cmp){
    size_t medio = (n / 2) -1;
    for(int i = medio; i>0; i--){
        downheap_aux(vector, medio, cmp, n);
    }
}


bool vector_redimensionar(void* vector, size_t tamNuevo) {
    int* datosNuevos = realloc(vector, tamNuevo * sizeof(void*));
    if (tamNuevo > 0 && datosNuevos == NULL) {
        return false;
    }

    vector->vector = datosNuevos;
    vector->tam = tamNuevo;
    return true;
}


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
    heapNuevo->capacidad = n;
    heapNuevo->cmp = cmp_func_t;
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
    if (heap->cantidad == heap->capacidad -1){
        if(vector_redimensionar(heap->vector,heap->capacidad * FACTOR_REDIM) == false){
            return false;
        }
    }
    heap->vector[heap->cantidad] = elem;
    heap->cantidad += 1;
    // TODO: UPHEAP
    return true; // FIXME: return(upheap(heap,elem))
}


void *heap_desencolar(heap_t *heap){
    if(heap->cantidad == 0){
        return NULL;
    }
    void* datoDevolver = heap->vector[0];

    swap(heap->vector,0,heap->cantidad-1);
    heap->cantidad -= 1;
    heap->vector[heap->cantidad] = NULL;
    downheap(heap,0);

    if (heap->cantidad * CONDICION_DISMINUCION <= heap->capacidad) && (heap->capacidad > TAM_INICIAL){
        vector_redimensionar(heap->vector,heap->capacidad / FACTOR_REDIM);
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



void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos,cant,cmp);

    for(int i = 1; i < cant; i++){
        swap(elementos,0,cant-i);
        downheap_aux(elementos, 0, cmp, cant-i);
    }
}
