#include <glib.h>
#include "u_log.h"
#include "u_alloc.h"
#include "u_array.h"

struct u_array {
    GPtrArray *gptr_arr;
};

struct u_array *
u_array_init(void)
{
    GPtrArray *gptr_arr;
    struct u_array *array;

    gptr_arr = g_ptr_array_new();
    if (!gptr_arr) {
        u_warn("Failed to create new pointer array!\n");
        return NULL;
    }

    array = u_malloc(sizeof(struct u_array));
    if (!array) {
        g_ptr_array_unref(gptr_arr);
        return NULL;
    }

    array->gptr_arr = gptr_arr;
    return array;
}

void
u_array_fini(struct u_array *array)
{
    g_ptr_array_unref(array->gptr_arr);
    u_free(array);
}

void
u_array_add(struct u_array *array, void *data)
{
    g_ptr_array_add(array->gptr_arr, data);
}

void *
u_array_index(struct u_array *array, int index)
{
    return g_ptr_array_index(array->gptr_arr, index);
}

unsigned
u_array_length(struct u_array *array)
{
    return array->gptr_arr->len;
}
