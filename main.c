#include "o_array_dyn.h"

#include <stdlib.h>

#include <stdio.h>

int main(void){
    o_array x;
    void* datap = NULL;

    /* o_array* arr  */
    o_init_arr(&x); //initialize o_array struct

    /* int size, void* data, o_array arr */ 
    o_push_elem(2, "a", &x); // out => 'a' '\0', size = 2, adds another available element

    /* int index, void** datap, o_array* arr */
    o_fetch_elem(1, &datap, &x); // fetches value of element with index 1

    printf("%s", (const char*)datap); 

    /* o_array* arr */
    o_pop_elem(&x); //remove the last array's element

    free(datap);

    o_push_elem(2, "b", &x); // out => 'b' '\0', size = 2

    o_fetch_elem(1, &datap, &x); 

    printf("%s", (const char*)datap);

    /* o_array* arr */
    o_uninit_arr(&x); // uninitialize elements and frees the array
}

