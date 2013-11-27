#ifndef U_ARRAY_H
#define U_ARRAY_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

struct u_array;

struct u_array *
u_array_init(void);

void
u_array_fini(struct u_array *array);

void
u_array_add(struct u_array *array, void *data);

void *
u_array_index(struct u_array *array, unsigned index);

unsigned
u_array_length(struct u_array *array);

#endif /* U_ARRAY_H */
