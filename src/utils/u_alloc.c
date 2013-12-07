#include <glib.h>
#include "u_assert.h"
#include "u_log.h"
#include "u_alloc.h"

void *
u_malloc(size_t size)
{
    void *ptr;

    if (size == 0)
        u_error("Memory allocation request of zero size!\n");

    ptr = u_calloc(1, size);
    u_assert(ptr);

    return ptr;
}

void *
u_calloc(size_t nmemb, size_t size)
{
    void *ptr;
    size_t tot;

    tot = nmemb * size;
    if (tot == 0)
        u_error("Memory allocation request of zero size!\n");

    ptr = g_try_malloc0(tot);
    u_assert(ptr);

    return ptr;
}

void
u_free(void *ptr)
{
    if (!ptr)
        u_error("Request to free NULL pointer!\n");
    g_free(ptr);
}
