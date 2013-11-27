#ifndef U_DICT_H
#define U_DICT_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

struct u_dict;

struct u_dict *u_dict_init(void);

void u_dict_fini(struct u_dict *dict);

void u_dict_add(struct u_dict *dict, char *key, void *data);

void *u_dict_get(struct u_dict *dict, const char *key);

typedef void (*u_dict_foreach)(void *key, void *value);
void u_dict_iter(struct u_dict *dict, u_dict_foreach func);

#endif /* U_DICT_H */
