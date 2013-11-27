#include <glib.h>
#include "u_log.h"
#include "u_alloc.h"
#include "u_dict.h"

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
