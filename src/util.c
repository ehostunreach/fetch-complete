#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <glib.h>
#include "util.h"

void
u_log(int level, const char *format, ...)
{
    va_list ap;

    level = (level == U_WARN) ? G_LOG_LEVEL_WARNING : G_LOG_LEVEL_CRITICAL;

    va_start(ap, format);
    g_logv(G_LOG_DOMAIN, level, format, ap);
    va_end(ap);
}

void *
u_malloc(size_t size)
{
    void *ptr;

    if (size == 0)
        u_warn("Memory allocation request of zero size!\n");

    ptr = malloc(size);
    if (!ptr)
        u_warn("Out of memory!\n");

    return ptr;
}

void *
u_calloc(size_t nmemb, size_t size)
{
    void *ptr;
    size_t tot;

    tot = nmemb * size;
    if (tot == 0)
        u_warn("Memory allocation request of zero size!\n");

    ptr = calloc(nmemb, size);
    if (!ptr)
        u_warn("Out of memory!\n");

    return ptr;
}

void
u_free(void *ptr)
{
    if (!ptr)
        u_warn("Request to free NULL pointer!\n");

    free(ptr);
}

size_t
u_strlen(const char *str)
{
    if (!str)
        u_error("Request to count NULL-string length!\n");

    return strlen(str);
}

char *
u_strdup(const char *str)
{
    char *ret;

    if (!str)
        u_error("Request to duplicate NULL string!\n");

    ret = strdup(str);
    if (!ret) {
        u_warn("String duplication failed!\n");
        return NULL;
    }

    return ret;
}

struct u_array {
    GPtrArray *gptr_arr;
};

struct u_array *
u_array_init(void)
{
    GPtrArray *gptr_arr;
    struct u_array *array;

    gptr_arr = g_ptr_array_new();
    if (!gptr_arr) {
        u_warn("Failed to create new pointer array!\n");
        return NULL;
    }

    array = u_malloc(sizeof(struct u_array));
    if (!array) {
        g_ptr_array_unref(gptr_arr);
        return NULL;
    }

    array->gptr_arr = gptr_arr;
    return array;
}

void
u_array_fini(struct u_array *array)
{
    g_ptr_array_unref(array->gptr_arr);
    u_free(array);
}

void
u_array_add(struct u_array *array, void *data)
{
    g_ptr_array_add(array->gptr_arr, data);
}

void *
u_array_index(struct u_array *array, int index)
{
    return g_ptr_array_index(array->gptr_arr, index);
}

unsigned
u_array_length(struct u_array *array)
{
    return array->gptr_arr->len;
}

struct u_dict {
    GHashTable *ht;
};

struct u_dict *
u_dict_init(void)
{
    GHashTable *ghtable;
    struct u_dict *dict;

    ghtable = g_hash_table_new(g_str_hash, g_str_equal);
    if (!ghtable) {
        u_warn("Failed to create new dictionary!\n");
        return NULL;
    }

    dict = u_malloc(sizeof(struct u_dict));
    if (!dict) {
        g_hash_table_destroy(ghtable);
        return NULL;
    }

    dict->ht = ghtable;
    return dict;
}

void
u_dict_fini(struct u_dict *dict)
{
    g_hash_table_destroy(dict->ht);
    u_free(dict);
}

void
u_dict_add(struct u_dict *dict, char *key, void *data)
{
    g_hash_table_insert(dict->ht, (gpointer) key, data);
}

void *
u_dict_get(struct u_dict *dict, const char *key)
{
    return g_hash_table_lookup(dict->ht, key);
}

void
u_dict_iter(struct u_dict *dict, u_dict_foreach func)
{
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, dict->ht);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        func(key, value);
    }
}
