#include <glib.h>
#include "u_assert.h"
#include "u_misc.h"

char *
u_getenv(const char *name)
{
    char *value;

    u_assert(name);

    value = g_getenv(name);
    if (!value)
        return NULL;

    return u_strdup(value);
}
