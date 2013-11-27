#ifndef U_LOG_H
#define U_LOG_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

#define U_WARN      1
#define U_ERROR     2

void
u_log(int level, const char *format, ...);

#define u_warn(format, ...)                                              \
do {                                                                     \
    u_log(U_WARN, "[%s:%d] " format, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

#define u_error(format, ...)                                                 \
do {                                                                         \
    u_log(U_ERROR, "[%s:%d] " format, __FILE__, __LINE__, ##__VA_ARGS__);    \
} while (0)

#endif /* U_LOG_H */
