#include "o_array_dyn.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

int o_valid_index(int, int, o_array);
o_array_err o_realloc_vpp(int, void***);

struct { o_array_err code; const char* message; } o_arr_errs[O_ERR_AMNT] = {
   { o_alloc_failed, "failed to allocate memory" },
   { o_success, "success" },
   { o_invalid_index, "the index isnt valid" }
};

o_array_err o_handle_errs(int code){
    if(code > O_ERR_AMNT){
        printf("code isn't valid \n");
        return -1;
    }
    
    printf("%s", o_arr_errs[(o_array_err)code].message);
       
    return code;
}

o_array_err o_init_arr(o_array* arr){
    arr->increment = 0;

    arr->data = NULL;

    return o_success;
}

o_array_err o_push_elem(int size, void* data, o_array* arr){
    o_array_err oar;

    ++arr->increment;

    oar = o_realloc_vpp(arr->increment, &arr->data); //add another index to the array

    if(oar == o_success){
       oar = o_insert_elem(arr->increment, size, data, arr);
    }

    return oar;
}

o_array_err o_insert_elem(int index, int size, void* data, o_array* arr){
    if(!o_valid_index(index, 0, *arr)){
        return o_invalid_index;
    }

    arr->data[index] = realloc(arr->data[index], size); //free &OR allocate memory for the element

    if(arr->data[index] == NULL){
        return o_alloc_failed;
    }

    memcpy(arr->data[index], data, size); //copy the memory from data to the element

    return o_success;
}

o_array_err o_pop_elem(o_array* arr){
    return o_remove_elem( arr->increment, arr); //pop the last element of the array
}

o_array_err o_remove_elem(int index, o_array* arr){
    void** vpp = NULL;
    o_array_err ot;

    if(!o_valid_index(index, 1, *arr)){
        return o_invalid_index;
    }

    if(arr->increment > 0){
        --arr->increment; //as we are removing an element, if there was an element pushed before this makes the count right
    }

    ot = o_realloc_vpp(arr->increment, &vpp); //alloc memory for the replacement array

    if(ot != o_success){
        return ot;
    }

    memcpy(vpp, arr->data - index, arr->increment); //copy memory from before the index to the rp array

    memcpy(vpp + index, arr->data + index, arr->increment); //copy memory from after

    arr->data = vpp; //arr data now points to what vpp is pointing to

    return o_success;
}

o_array_err o_fetch_elem(int index, void** datap, o_array* arr){
    if(!o_valid_index(index, 1, *arr)){
        return o_invalid_index;
    }

    *datap = arr->data[index]; //datap points to what *arr->data+index is pointing to

    return o_success;
}

void o_free_arr(o_array* arr){
    int i;

    if(arr->data){
        for(i = 0; i < arr->increment; i++){
            if(arr->data[i] == NULL){
                continue;
            }

            free(arr->data[i]);
        }
        free(arr->data);
    }
}

int o_valid_index(int index, int nc, o_array arr){
    if(nc && arr.data[index] == NULL) {
        return 0;
    }

    return index >= 0 && index <= arr.increment;
}

o_array_err o_realloc_vpp(int size, void*** arr){
    *arr = realloc(*arr, size); 

    if(*arr == NULL){
        return o_alloc_failed;
    }

    return o_success;
}
