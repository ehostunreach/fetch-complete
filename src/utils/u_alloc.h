#ifndef U_ALLOC_H
#define U_ALLOC_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

void *u_malloc(size_t size);
void *u_calloc(size_t nmemb, size_t size);
void u_free(void *ptr);

#endif /* U_ALLOC_H */
