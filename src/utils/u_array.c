#include <glib.h>
#include "u_assert.h"
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
    u_assert(gptr_arr);

    array = u_malloc(sizeof(struct u_array));
    array->gptr_arr = gptr_arr;

    return array;
}

void
u_array_fini(struct u_array *array)
{
    u_assert(array && array->gptr_arr);

    g_ptr_array_unref(array->gptr_arr);
    u_free(array);
}

void
u_array_add(struct u_array *array, void *data)
{
    /* we do not allow NULL elements */
    u_assert(array && data);

    g_ptr_array_add(array->gptr_arr, data);
}

void *
u_array_index(struct u_array *array, unsigned index)
{
    u_assert(array && (index < u_array_length(array)));

    return g_ptr_array_index(array->gptr_arr, index);
}

unsigned
u_array_length(struct u_array *array)
{
    u_assert(array);

    return array->gptr_arr->len;
}
