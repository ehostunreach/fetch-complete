#ifndef U_STRING_H
#define U_STRING_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

size_t u_strlen(const char *msg);
char *u_strdup(const char *str);

#endif /* U_STRING_H */
