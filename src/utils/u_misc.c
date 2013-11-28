#include <glib.h>
#include "u_assert.h"
#include "u_log.h"
#include "u_string.h"
#include "u_misc.h"

char *
u_getenv(const char *name)
{
    const char *value;

    u_assert(name);

    value = g_getenv(name);
    if (!value)
        return NULL;

    return u_strdup(value);
}

int
u_parse_shell_args(const char *command_line,
                   int *argcp, char ***argvp)
{
    u_assert(command_line && argcp && argvp);

    if (!g_shell_parse_argv(command_line, argcp, argvp, NULL)) {
        u_warn("Unable to parse command line!\n");
        return 1;
    }

    return 0;
}
