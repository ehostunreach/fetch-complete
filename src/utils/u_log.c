#include <stdlib.h>
#include <stdarg.h>
#include <glib.h>
#include "u_log.h"

void
u_log(int level, const char *format, ...)
{
    va_list ap;

    level = (level == U_WARN) ? G_LOG_LEVEL_WARNING : G_LOG_LEVEL_CRITICAL;

    va_start(ap, format);
    g_logv(G_LOG_DOMAIN, level, format, ap);
    va_end(ap);

    if (level == G_LOG_LEVEL_CRITICAL)
        abort();
}
