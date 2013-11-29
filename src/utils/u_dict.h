#ifndef U_DICT_H
#define U_DICT_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

typedef int (*u_dict_foreach)(void *key, void *value);
typedef void (*u_dict_free)(void *data);

typedef unsigned (*u_hash_func)(const void *key);
unsigned u_direct_hash(const void *key);
unsigned u_str_hash(const void *key);
unsigned u_int_hash(const void *key);

typedef int (*u_equal_func)(const void *a, const void *b);
int u_direct_equal(const void *a, const void *b);
int u_str_equal(const void *a, const void *b);

struct u_dict;

struct u_dict *u_dict_init(void);

struct u_dict *u_dict_init_full(u_hash_func hash_func,
                                u_equal_func equal_func,
                                u_dict_free key_destroy,
                                u_dict_free value_destroy);

void u_dict_fini(struct u_dict *dict);

void u_dict_add(struct u_dict *dict, char *key, void *data);

void *u_dict_get(struct u_dict *dict, const char *key);

int u_dict_iter(struct u_dict *dict, u_dict_foreach func);

#endif /* U_DICT_H */
