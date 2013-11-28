#ifndef U_MISC_H
#define U_MISC_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

char *u_getenv(const char *name);

int u_parse_shell_args(const char *command_line,
                       int *argcp, char ***argvp);

#endif /* U_MISC_H */
