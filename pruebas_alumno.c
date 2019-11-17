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
    printf("\n prueba heap vacio\n");
	heap_t* heap = heap_crear(NULL);
	print_test("Heap creado correctamente" , heap != NULL);
	print_test("La cantidad de elementos es cero" , heap_cantidad(heap) == 0);
	print_test("El heap esta vacio" , heap_esta_vacio(heap) == true);
	print_test("Heap no tiene maximo" , heap_ver_max(heap) == NULL);
	print_test("Heap no puede desencolar" , heap_desencolar(heap) == NULL);
	heap_destruir(heap , NULL);
}


void prueba_heap_encolar(){
    printf("\n prueba heap encolar\n");
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
    print_test("El maximo debe ser item1", heap_ver_max(heap) == &item2);
    print_test("Insertar NULL es invalido", heap_encolar(heap, NULL) == false);
    print_test("Desencolo primer elemento", heap_desencolar(heap) == &item2);
    print_test("La cantidad de elementos debe ser 3", heap_cantidad(heap) == 3);

    for(int i = 0; i < 3; i++){
		heap_desencolar(heap);
	}

    print_test("El heap esta vacio", heap_esta_vacio(heap) == true);
    heap_destruir(heap, NULL);
}


void prueba_heap_desencolar(){
    printf("\nprueba heap desencolar\n");
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

    print_test("\nDesencolo primer elemento", heap_desencolar(heap) == &item2);
    print_test("La cantidad de elementos debe ser 3", heap_cantidad(heap) == 3);
    print_test("El maximo debe ser item4", heap_ver_max(heap) == &item4);

    print_test("\nDesencolo primer elemento", heap_desencolar(heap) == &item4);
    print_test("La cantidad de elementos debe ser 2", heap_cantidad(heap) == 2);
    print_test("El maximo debe ser item1", heap_ver_max(heap) == &item1);
    //printf("%d\n",*(int*)heap_ver_max(heap));

    print_test("\nDesencolo primer elemento", heap_desencolar(heap) == &item1);
    print_test("La cantidad de elementos debe ser 1", heap_cantidad(heap) == 1);
    print_test("El maximo debe ser item3", heap_ver_max(heap) == &item3);

    print_test("\nDesencolo primer elemento", heap_desencolar(heap) == &item3);
    print_test("La cantidad de elementos debe ser 0", heap_cantidad(heap) == 0);
    print_test("El maximo debe ser NULL", heap_ver_max(heap) == NULL);


    print_test("\nEl heap esta vacio", heap_esta_vacio(heap) == true);
    heap_destruir(heap, NULL);
}


int main(){
    //prueba_heap_vacio();
    //prueba_heap_encolar();
    prueba_heap_desencolar();
    return 0;
}
