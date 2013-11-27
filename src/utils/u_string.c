#include <glib.h>
#include "u_log.h"
#include "u_string.h"

size_t
u_strlen(const char *str)
{
    u_assert(str);

    return g_utf8_strlen(str, -1);
}

char *
u_strdup(const char *str)
{
    char *ret;

    u_assert(str);
    ret = g_strdup(str);
    u_assert(ret);

    return ret;
}
