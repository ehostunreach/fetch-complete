#include <glib.h>
#include "u_assert.h"
#include "u_log.h"
#include "u_alloc.h"
#include "u_dict.h"

unsigned
u_direct_hash(const void *key)
{
    return g_direct_hash(key);
}

unsigned
u_str_hash(const void *key)
{
    return g_str_hash(key);
}

unsigned
u_int_hash(const void *key)
{
    return g_int_hash(key);
}

int
u_direct_equal(const void *a, const void *b)
{
    return g_direct_equal(a, b);
}

int
u_str_equal(const void *a, const void *b)
{
    return g_str_equal(a, b);
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
    u_assert(ghtable);

    dict = u_malloc(sizeof(struct u_dict));
    dict->ht = ghtable;
    return dict;
}

struct u_dict *
u_dict_init_full(u_hash_func hash_func,
                 u_equal_func equal_func,
                 u_dict_free key_destroy,
                 u_dict_free value_destroy)
{
    GHashTable *ghtable;
    struct u_dict *dict;

    ghtable = g_hash_table_new_full(hash_func, equal_func,
                                    key_destroy, value_destroy);
    u_assert(ghtable);

    dict = u_malloc(sizeof(struct u_dict));
    dict->ht = ghtable;
    return dict;
}

void
u_dict_fini(struct u_dict *dict)
{
    u_assert(dict);

    g_hash_table_destroy(dict->ht);
    u_free(dict);
}

void
u_dict_add(struct u_dict *dict, char *key, void *data)
{
    u_assert(dict && key);

    g_hash_table_insert(dict->ht, (gpointer) key, data);
}

void *
u_dict_get(struct u_dict *dict, const char *key)
{
    u_assert(dict && key);

    return g_hash_table_lookup(dict->ht, key);
}

int
u_dict_iter(struct u_dict *dict, u_dict_foreach func)
{
    GHashTableIter iter;
    gpointer key, value;

    u_assert(dict && func);

    g_hash_table_iter_init(&iter, dict->ht);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (func(key, value))
            return 1;
    }

    return 0;
}
