#ifndef UTIL_H
#define UTIL_H

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

void *u_malloc(size_t size);
void *u_calloc(size_t nmemb, size_t size);
void u_free(void *ptr);

size_t u_strlen(const char *msg);
char *u_strdup(const char *str);

struct u_array;

struct u_array *
u_array_init(void);

void
u_array_fini(struct u_array *array);

void
u_array_add(struct u_array *array, void *data);

void *
u_array_index(struct u_array *array, int index);

unsigned
u_array_length(struct u_array *array);

struct u_dict;

struct u_dict *
u_dict_init(void);

void
u_dict_fini(struct u_dict *dict);

void
u_dict_add(struct u_dict *dict, char *key, void *data);

void *
u_dict_get(struct u_dict *dict, const char *key);

typedef void (*u_dict_foreach)(void *key, void *value);

void
u_dict_iter(struct u_dict *dict, u_dict_foreach func);

#endif /* UTIL_H */
