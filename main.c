#include "o_array_dyn.h"

#include <stdlib.h>

#include <stdio.h>

int main(void){
    o_array x;
    void* datap = NULL;

    o_alloc_arr(&x);

    o_push_elem(2, "a", &x); // 'a' '\0'

    o_fetch_elem(1, &datap, &x); // push adds another available index.

    printf("%s", (const char*)datap);

    o_pop_elem(&x);

    free(datap);

    o_push_elem(2, "b", &x);

    o_fetch_elem(1, &datap, &x);

    printf("%s", (const char*)datap);

    o_free_arr(&x);
}

