#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



int comparacion(const void* i, const void* j){
    if (i == NULL){
        return -1;
    }
    if (j == NULL){
        return 1;
    }

    if(*(int*)i < *(int*)j){
        return -1;
    }else if (*(int*)i > *(int*)j){
        return 1;
    }else{
        return 0;
    }
}


void prueba_heap_vacio(){
    printf("\nPrueba heap vacio\n");
	heap_t* heap = heap_crear(NULL);
	print_test("Heap creado correctamente" , heap != NULL);
	print_test("La cantidad de elementos es cero" , heap_cantidad(heap) == 0);
	print_test("El heap esta vacio" , heap_esta_vacio(heap) == true);
	print_test("Heap no tiene maximo" , heap_ver_max(heap) == NULL);
	print_test("Heap no puede desencolar" , heap_desencolar(heap) == NULL);
	heap_destruir(heap , NULL);
}


void prueba_heap_encolar(){
    printf("\nPrueba heap encolar\n");
    heap_t* heap = heap_crear(comparacion);
    int item1 = 5;
    int item2 = 1;
    int item3 = 9;
    int item4 = 3;

    print_test("Heap creado correctamente" , heap != NULL);
    print_test("Insertando item1" , heap_encolar(heap,&item1));
    print_test("El heap no esta vacio" , heap_esta_vacio(heap) != true);
    print_test("La cantidad de elementos debe ser 1", heap_cantidad(heap) == 1);
    print_test("El maximo es item1", heap_ver_max(heap) == &item1);
    print_test("Insertando item2" , heap_encolar(heap,&item2));
    print_test("Insertando item3" , heap_encolar(heap,&item3));
    print_test("Insertando item4" , heap_encolar(heap,&item4));
    print_test("La cantidad de elementos debe ser 4", heap_cantidad(heap) == 4);
    print_test("El maximo es item3", heap_ver_max(heap) == &item3);
    print_test("Insertar NULL es invalido", heap_encolar(heap, NULL) == false);
    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item3);
    print_test("La cantidad de elementos debe ser 3", heap_cantidad(heap) == 3);

    for(int i = 0; i < 3; i++){
		heap_desencolar(heap);
	}

    print_test("El heap esta vacio", heap_esta_vacio(heap) == true);
    heap_destruir(heap, NULL);
}


void prueba_heap_desencolar(){
    printf("\nPrueba heap desencolar\n");
    heap_t* heap = heap_crear(comparacion);
    int item1 = 5;
    int item2 = 1;
    int item3 = 9;
    int item4 = 3;

    print_test("Heap creado correctamente" , heap != NULL);
    print_test("Insertando item1" , heap_encolar(heap,&item1));
    print_test("El heap no esta vacio" , heap_esta_vacio(heap) != true);
    print_test("La cantidad de elementos debe ser 1", heap_cantidad(heap) == 1);
    print_test("El maximo debe ser item1", heap_ver_max(heap) == &item1);
    print_test("Insertando item2" , heap_encolar(heap,&item2));
    print_test("Insertando item3" , heap_encolar(heap,&item3));
    print_test("Insertando item4" , heap_encolar(heap,&item4));
    print_test("La cantidad de elementos debe ser 4", heap_cantidad(heap) == 4);

    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item3);
    print_test("La cantidad de elementos debe ser 3", heap_cantidad(heap) == 3);
    print_test("El maximo es item1", heap_ver_max(heap) == &item1);

    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item1);
    print_test("La cantidad de elementos debe ser 2", heap_cantidad(heap) == 2);
    print_test("El maximo es item4", heap_ver_max(heap) == &item4);

    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item4);
    print_test("La cantidad de elementos debe ser 1", heap_cantidad(heap) == 1);
    print_test("El maximo es item2", heap_ver_max(heap) == &item2);

    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item2);
    print_test("La cantidad de elementos debe ser 0", heap_cantidad(heap) == 0);
    print_test("El maximo es NULL", heap_ver_max(heap) == NULL);

    print_test("El heap esta vacio", heap_esta_vacio(heap) == true);
    heap_destruir(heap, NULL);
}


void prueba_heap_destruir(){
    printf("\nPrueba heap destruir\n");
    heap_t *heap = heap_crear(comparacion);
    int *item1 = malloc(sizeof(int));
    int *item2 = malloc(sizeof(int));
    int *item3 = malloc(sizeof(int));
    *item1 = 5;
    *item2 = 1;
    *item3 = 22;

    print_test("Insertar item1", heap_encolar(heap, item1));
    print_test("Insertar item3", heap_encolar(heap, item3));
    print_test("Insertar item2", heap_encolar(heap, item2));
    print_test("El maximo es item3", heap_ver_max(heap) == item3);
    print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("El heap no esta vacio", heap_esta_vacio(heap) == false);
    print_test("Desencolar elemento es item3", heap_desencolar(heap) == item3);
    heap_destruir(heap, free);
    free(item3);
}


void prueba_heap_sort(){
    printf("\nPrueba heap destruir\n");
    int uno = 1;
    int siete = 7;
    int cinco = 5;
    int seis = 6;
    int once = 11;
    int nueve = 9;
    int vdos = 22;
    int cincuenta = 50;
    int* vector_prueba[8] = {&uno,&once,&cincuenta,&seis,&vdos,&nueve,&cinco,&siete};
    int* vector_ordenado[8] ={&uno, &cinco, &seis, &siete, &nueve, &once, &vdos, &cincuenta};
    printf("Vector de prueba:\n");
    for(int i = 0; i < 8 ; i++){
        printf("%d " , *vector_prueba[i]);
    }

    heap_sort((void**)vector_prueba, 8 , comparacion);

    printf("\nVector de pruebas despues de heapsort:\n");
    for(int i = 0; i < 8 ; i++){
        printf("%d " , *vector_prueba[i]);
    }

    bool ordenado = true;
    for(int i = 0; i < 8 ; i++){
    	if(vector_prueba[i] != vector_ordenado[i]){
    	ordenado = false;
        }
    }
    print_test("\nEl vector fue ordenado correctamente", ordenado);
}


void prueba_crear_con_arreglo(){
    printf("\nPrueba armar heap con arreglo\n");
    int uno = 1;
    int siete = 7;
    int cinco = 5;
    int seis = 6;
    int once = 11;
    int nueve = 9;
    int* vector_prueba[6] = {&uno,&cinco,&seis,&siete,&nueve,&once};
    heap_t* heap = heap_crear_arr((void**)vector_prueba,6,comparacion);

    for(int i = 0; i < 6; i++){
        printf("la cantidad es %d",6-i);
        print_test(" ", heap_cantidad(heap) == (6-i));
        printf("desencolar devuelve %d",*(int*)vector_prueba[5-i]);
        print_test(" ", heap_desencolar(heap) == vector_prueba[5-i]);
    }

    print_test("La cantidad de elementos es cero" , heap_cantidad(heap) == 0);
    print_test("Heap esta vacio" , heap_esta_vacio(heap) == true);
    print_test("El maximo es NULL" , heap_ver_max(heap) == NULL);
    print_test("Heap no puede desencolar" , heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
}


void prueba_heap_volumen(size_t cant_elementos){
    printf("\nprueba de volumen\n");
    heap_t *heap = heap_crear(comparacion);
    int* vector[cant_elementos];

    for (int i = 0; i < cant_elementos; i++) {
        int *elemento = malloc(sizeof(int));
        *elemento = i;
        vector[i] = elemento;
    }

    bool encolar_correcto = true;
    for (int i = 0; i < cant_elementos; i++) {
        if(!heap_encolar(heap, vector[i])){
            encolar_correcto = false;
            break;
        }
    }

    printf("Se encolaron %ld elementos correctamente" , cant_elementos);
    print_test("" , encolar_correcto == true);

    while(heap_cantidad(heap) != 0){
        free(heap_desencolar(heap));
    }

    print_test("Se desencolaron todos los elementos", heap_cantidad(heap) == 0);
    heap_destruir(heap, free);
}


int main(){
    prueba_heap_vacio();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_heap_destruir();
    prueba_heap_volumen(1020);
    prueba_crear_con_arreglo();
    prueba_heap_sort();
    return 0;
}
