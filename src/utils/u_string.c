#include <glib.h>
#include "u_log.h"
#include "u_string.h"

size_t
u_strlen(const char *str)
{
    if (!str)
        u_error("Request to count NULL-string length!\n");

    return g_utf8_strlen(str, -1);
}

char *
u_strdup(const char *str)
{
    char *ret;

    if (!str)
        u_error("Request to duplicate NULL string!\n");

    ret = g_strdup(str);
    if (!ret) {
        u_warn("String duplication failed!\n");
        return NULL;
    }

    return ret;
}
