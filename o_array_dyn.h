#ifndef OARR_C
#define OARR_C

#define O_ERR_AMNT 3

typedef struct {
   int increment;
   void** data;
} o_array;

typedef enum {
   o_alloc_failed = 0,
   o_success = 1,
   o_invalid_index = 2
} o_array_err;

o_array_err o_handle_errs(int); //handle and display messages for errors ( should be called by the end user )

o_array_err o_init_arr(o_array*); //initialize struct

o_array_err o_push_elem(int, void*, o_array*); //allocate one more index and push item

o_array_err o_insert_elem(int, int, void*, o_array*); //allocate memory and replace item of index

o_array_err o_pop_elem(o_array*); //pop current index

o_array_err o_remove_elem(int, o_array*); //remove item with a certain index

o_array_err o_fetch_elem(int, void**, o_array*); //fetch item data
 
void o_free_arr(o_array*); //free all allocated data

#endif // OARR_C
